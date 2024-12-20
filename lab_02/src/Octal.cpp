#include "../include/Octal.hpp"
#include <algorithm>
#include <stdexcept>
#include <cstring>

Octal::Octal() : data_(nullptr), size_(0), capacity_(0) {}

Octal::Octal(size_t n, unsigned char t) : size_(n), capacity_(n), data_(new unsigned char[n]) {
    if (t > 7)
        throw std::invalid_argument("Invalid octal digit");
    std::fill(data_, data_ + n, t);
}

Octal::Octal(const std::string &other) : size_(other.size()), capacity_(other.size()), data_(new unsigned char[other.size()]) {
    for (size_t i = 0; i < size_; ++i) {
        if (other[i] < '0' || other[i] > '7')
            throw std::invalid_argument("Invalid character in octal string");
        data_[size_ - i - 1] = other[i] - '0';
    }
}

Octal::Octal(const Octal &other) : size_(other.size_), capacity_(other.capacity_), data_(new unsigned char[other.capacity_]) {
    std::copy(other.data_, other.data_ + other.size_, data_);
}

Octal::Octal(Octal &&other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

Octal::Octal(const std::initializer_list<unsigned char> &other) : size_(other.size()), capacity_(other.size()), data_(new unsigned char[other.size()]) {
    size_t i = 0;
    for (const auto &digit : other) {
        if (digit > 7)
            throw std::invalid_argument("Invalid octal digit in initializer list");
        data_[i++] = digit;
    }
}

Octal &Octal::operator=(const Octal &other) {
    if (this != &other) {
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new unsigned char[capacity_];
        std::copy(other.data_, other.data_ + size_, data_);
    }
    return *this;
}

Octal &Octal::operator=(Octal &&other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

size_t Octal::Size() const noexcept { return size_; }
size_t Octal::Capacity() const noexcept { return capacity_; }

std::string Octal::toString() const {
    std::string result(size_, '0');
    for (size_t i = 0; i < size_; ++i)
        result[size_ - i - 1] = data_[i] + '0';
    return result;
}

void Octal::Clear() noexcept {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

void Octal::push_back(unsigned char digit) {
    if (digit > 7)
        throw std::invalid_argument("Invalid octal digit");
    if (size_ == capacity_) {
        capacity_ = capacity_ ? capacity_ * 2 : 1;
        unsigned char *newData = new unsigned char[capacity_];
        std::copy(data_, data_ + size_, newData);
        delete[] data_;
        data_ = newData;
    }
    data_[size_++] = digit;
}

void Octal::push_front(unsigned char digit) {
    if (digit > 7)
        throw std::invalid_argument("Invalid octal digit");
    if (size_ == capacity_) {
        capacity_ = capacity_ ? capacity_ * 2 : 1;
        unsigned char *newData = new unsigned char[capacity_];
        std::copy(data_, data_ + size_, newData + 1);
        delete[] data_;
        data_ = newData;
    }
    else {
        std::move_backward(data_, data_ + size_, data_ + size_ + 1);
    }
    data_[0] = digit;
    ++size_;
}

Octal Octal::operator+(const Octal &other) const {
    size_t maxSize = std::max(size_, other.size_);
    Octal result;
    result.capacity_ = maxSize + 1;
    result.data_ = new unsigned char[result.capacity_];
    result.size_ = 0;

    unsigned char carry = 0;
    for (size_t i = 0; i < maxSize || carry; ++i) {
        unsigned char sum = carry;
        if (i < size_)
            sum += data_[i];
        if (i < other.size_)
            sum += other.data_[i];
        carry = sum >= 8;
        result.data_[result.size_++] = sum % 8;
    }

    return result;
}

Octal Octal::operator-(const Octal &other) const {
    if (*this < other)
        throw std::invalid_argument("Result cannot be negative");

    Octal result;
    result.capacity_ = size_;
    result.data_ = new unsigned char[result.capacity_];
    result.size_ = 0;

    unsigned char borrow = 0;
    for (size_t i = 0; i < size_; ++i) {
        unsigned char diff = data_[i] - borrow - (i < other.size_ ? other.data_[i] : 0);
        borrow = diff > data_[i];
        if (borrow)
            diff += 8;
        result.data_[result.size_++] = diff;
    }

    while (result.size_ > 1 && result.data_[result.size_ - 1] == 0)
        --result.size_;

    return result;
}

bool Octal::operator<(const Octal &other) const {
    if (size_ != other.size_)
        return size_ < other.size_;
    for (size_t i = size_; i-- > 0;) {
        if (data_[i] != other.data_[i])
            return data_[i] < other.data_[i];
    }
    return false;
}

bool Octal::operator>(const Octal &other) const { return other < *this; }
bool Octal::operator==(const Octal &other) const {
    return size_ == other.size_ && std::equal(data_, data_ + size_, other.data_);
}
bool Octal::operator!=(const Octal &other) const { return !(*this == other); }

Octal::~Octal() { delete[] data_; }