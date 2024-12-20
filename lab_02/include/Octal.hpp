#pragma once

#include <string>
#include <initializer_list>

class Octal {
private:
    unsigned char *data_;
    size_t size_;
    size_t capacity_;

public:
    Octal();
    Octal(size_t n, unsigned char t = 0);
    Octal(const std::string &other);
    Octal(const Octal &other);
    Octal(Octal &&other) noexcept;
    Octal(const std::initializer_list<unsigned char> &other);

    Octal &operator=(const Octal &other);
    Octal &operator=(Octal &&other) noexcept;

    size_t Size() const noexcept;
    size_t Capacity() const noexcept;
    std::string toString() const;

    void Clear() noexcept;
    void push_back(unsigned char digit);
    void push_front(unsigned char digit);

    Octal operator+(const Octal &other) const;
    Octal operator-(const Octal &other) const;

    bool operator<(const Octal &other) const;
    bool operator>(const Octal &other) const;
    bool operator==(const Octal &other) const;
    bool operator!=(const Octal &other) const;

    ~Octal();
};
