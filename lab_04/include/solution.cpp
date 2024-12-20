#pragma once

#include <memory>
#include <vector>
#include <cmath>
#include <iostream>
#include <concepts>

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
struct Point {
    T x, y;
};

template <Scalar T>
class Figure {
public:
    virtual ~Figure() = default;
    virtual double area() const = 0;
    virtual Point<T> geometricCenter() const = 0;
    virtual void print(std::ostream& os) const = 0;
};

template <Scalar T>
class Hexagon : public Figure<T> {
    std::vector<Point<T>> points_;

public:
    explicit Hexagon(const std::vector<Point<T>>& points) : points_(points) {
        if (points.size() != 6) {
            throw std::invalid_argument("Hexagon must have 6 vertices.");
        }
    }

    double area() const override {
        double result = 0.0;
        for (size_t i = 0; i < points_.size(); ++i) {
            size_t j = (i + 1) % points_.size();
            result += points_[i].x * points_[j].y - points_[j].x * points_[i].y;
        }
        return std::abs(result) / 2.0;
    }

    Point<T> geometricCenter() const override {
        T x = 0, y = 0;
        for (const auto& point : points_) {
            x += point.x;
            y += point.y;
        }
        return {x / 6, y / 6};
    }

    void print(std::ostream& os) const override {
        os << "Hexagon: ";
        for (const auto& point : points_) {
            os << "(" << point.x << ", " << point.y << ") ";
        }
    }
};
