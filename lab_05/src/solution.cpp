#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <memory_resource>
#include <stdexcept>
#include <string>
#include <utility>
#include <cstddef>
#include <type_traits>
#include <memory_resource>

// Памятный ресурс, работающий с одним большим блоком и std::map для отслеживания свободных областей.
class BlockMemResource : public std::pmr::memory_resource {
public:
    explicit BlockMemResource(std::size_t total) 
        : totalSize_(total)
    {
        basePtr_ = std::malloc(totalSize_);
        if (!basePtr_) {
            throw std::bad_alloc();
        }
        freeSegments_[basePtr_] = totalSize_;
    }

    ~BlockMemResource() override {
        std::free(basePtr_);
    }

protected:
    void *do_allocate(std::size_t bytes, std::size_t alignment) override {
        for (auto it = freeSegments_.begin(); it != freeSegments_.end(); ++it) {
            void* blk = it->first;
            std::size_t blkSize = it->second;

            const std::size_t adj = calcAlignOffset(blk, alignment);
            const std::size_t need = bytes + adj;

            if (blkSize >= need) {
                void* alignedPtr = static_cast<std::byte*>(blk) + adj;
                freeSegments_.erase(it);

                const std::size_t leftover = blkSize - need;
                if (leftover > 0) {
                    void* remainder = static_cast<std::byte*>(alignedPtr) + bytes;
                    freeSegments_[remainder] = leftover;
                }

                return alignedPtr;
            }
        }
        throw std::bad_alloc();
    }

    void do_deallocate(void *p, std::size_t bytes, std::size_t /*alignment*/) override {
        if (!p || bytes == 0) {
            return;
        }
        freeSegments_[p] = bytes;
        mergeFreeSegments();
    }

    bool do_is_equal(const std::pmr::memory_resource &other) const noexcept override {
        return this == &other;
    }

private:
    void* basePtr_ = nullptr;
    std::size_t totalSize_;
    std::map<void*, std::size_t> freeSegments_;

    static std::size_t calcAlignOffset(void* p, std::size_t alignment) noexcept {
        const std::uintptr_t addr = reinterpret_cast<std::uintptr_t>(p);
        const std::size_t mis = addr % alignment;
        return (mis == 0) ? 0 : (alignment - mis);
    }

    void mergeFreeSegments() {
        if (freeSegments_.empty()) return;
        auto it = freeSegments_.begin();
        auto prev = it;
        ++it;
        while (it != freeSegments_.end()) {
            std::byte* prevEnd = static_cast<std::byte*>(prev->first) + prev->second;
            if (prevEnd == it->first) {
                prev->second += it->second;
                it = freeSegments_.erase(it);
            } else {
                prev = it;
                ++it;
            }
        }
    }
};

// Узел для однонаправленного списка
template <class T>
struct ForwardNode {
    T element;
    ForwardNode* next = nullptr;
};

template <class T, class Alloc = std::pmr::polymorphic_allocator<T>>
class ForwardChain {
    static_assert(std::is_default_constructible_v<T>, "T must be default constructible.");
    static_assert(std::is_same_v<Alloc, std::pmr::polymorphic_allocator<T>>, "Alloc must be polymorphic_allocator<T>.");

public:
    explicit ForwardChain(std::pmr::memory_resource *mr = std::pmr::get_default_resource()) noexcept
        : alloc_(mr), nodeAlloc_(mr), head_(nullptr) {}

    ForwardChain(const ForwardChain &other)
        : alloc_(other.alloc_), nodeAlloc_(other.nodeAlloc_), head_(nullptr) {
        for (auto &x : other) {
            appendItem(x);
        }
    }

    ForwardChain(ForwardChain &&other) noexcept
        : alloc_(other.alloc_), nodeAlloc_(other.nodeAlloc_), head_(other.head_) {
        other.head_ = nullptr;
    }

    ForwardChain &operator=(const ForwardChain &other) {
        if (this != &other) {
            cleanUp();
            for (auto &x : other) {
                appendItem(x);
            }
        }
        return *this;
    }

    ForwardChain &operator=(ForwardChain &&other) noexcept {
        if (this != &other) {
            cleanUp();
            head_ = other.head_;
            other.head_ = nullptr;
        }
        return *this;
    }

    ~ForwardChain() {
        cleanUp();
    }

    void appendItem(const T &value) {
        auto* newNode = makeNode(value);
        if (!head_) {
            head_ = newNode;
        } else {
            auto* cur = head_;
            while (cur->next) {
                cur = cur->next;
            }
            cur->next = newNode;
        }
    }

    void cleanUp() noexcept {
        while (head_) {
            auto* temp = head_->next;
            freeNode(head_);
            head_ = temp;
        }
    }

    [[nodiscard]] bool empty() const noexcept { return head_ == nullptr; }

    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        explicit iterator(ForwardNode<T>* p) noexcept : ptr_(p) {}

        reference operator*() const noexcept { return ptr_->element; }
        pointer operator->() const noexcept { return &ptr_->element; }
        iterator &operator++() noexcept { ptr_ = ptr_->next; return *this; }
        iterator operator++(int) noexcept { iterator tmp = *this; ptr_ = ptr_->next; return tmp; }
        bool operator==(const iterator &o) const noexcept { return ptr_ == o.ptr_; }
        bool operator!=(const iterator &o) const noexcept { return ptr_ != o.ptr_; }

    private:
        ForwardNode<T>* ptr_;
    };

    class const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        explicit const_iterator(const ForwardNode<T>* p) noexcept : ptr_(p) {}

        reference operator*() const noexcept { return ptr_->element; }
        pointer operator->() const noexcept { return &ptr_->element; }
        const_iterator &operator++() noexcept { ptr_ = ptr_->next; return *this; }
        const_iterator operator++(int) noexcept { const_iterator tmp = *this; ptr_ = ptr_->next; return tmp; }
        bool operator==(const const_iterator &o) const noexcept { return ptr_ == o.ptr_; }
        bool operator!=(const const_iterator &o) const noexcept { return ptr_ != o.ptr_; }

    private:
        const ForwardNode<T>* ptr_;
    };

    iterator begin() noexcept { return iterator(head_); }
    iterator end() noexcept { return iterator(nullptr); }

    const_iterator begin() const noexcept { return const_iterator(head_); }
    const_iterator end() const noexcept { return const_iterator(nullptr); }

private:
    using NodeAlloc = std::pmr::polymorphic_allocator<ForwardNode<T>>;

    ForwardNode<T>* makeNode(const T &val) {
        ForwardNode<T>* node = nodeAlloc_.allocate(1);
        std::allocator_traits<NodeAlloc>::construct(nodeAlloc_, node, ForwardNode<T>{val, nullptr});
        return node;
    }

    void freeNode(ForwardNode<T>* node) noexcept {
        // Используем std::allocator_traits для корректного уничтожения
        std::allocator_traits<NodeAlloc>::destroy(nodeAlloc_, node);
        nodeAlloc_.deallocate(node, 1);
    }

    Alloc alloc_;
    NodeAlloc nodeAlloc_;
    ForwardNode<T>* head_;
};