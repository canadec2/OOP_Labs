#pragma once
#include "figure.h"

class Triangle : public Figure {
private:
    std::vector<Point> vertices;
public:
    Triangle():vertices(3){}
    Triangle(const Triangle& other):vertices(other.vertices){}
    Triangle(Triangle&& other) noexcept : vertices(std::move(other.vertices)){}
    Triangle& operator=(const Triangle& other) {
        if (this!=&other) vertices=other.vertices;
        return *this;
    }
    Triangle& operator=(Triangle&& other) noexcept {
        if (this!=&other) vertices=std::move(other.vertices);
        return *this;
    }

    Figure* clone() const override {
        return new Triangle(*this);
    }

    bool operator==(const Figure& o) const override {
        const Triangle* h = dynamic_cast<const Triangle*>(&o);
        if (!h) return false;
        for (int i=0;i<3;i++){
            if (fabs(vertices[i].x - h->vertices[i].x)>1e-9 ||
                fabs(vertices[i].y - h->vertices[i].y)>1e-9) return false;
        }
        return true;
    }

    std::pair<double,double> center() const override {
        return polygonCenter(vertices);
    }

    void print(std::ostream &os) const override {
        os<<"Triangle: ";
        for (auto &p: vertices) {
            os<<"("<<p.x<<","<<p.y<<") ";
        }
    }

    void read(std::istream &is) override {
        for (int i=0;i<3;i++){
            is>>vertices[i].x>>vertices[i].y;
        }
    }

    double area() const override {
        return polygonArea(vertices);
    }
};