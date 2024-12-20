#pragma once
#include "figure.h"

class Octagon : public Figure {
private:
    std::vector<Point> vertices;
public:
    Octagon():vertices(8){}
    Octagon(const Octagon& other):vertices(other.vertices){}
    Octagon(Octagon&& other) noexcept : vertices(std::move(other.vertices)){}
    Octagon& operator=(const Octagon& other) {
        if (this!=&other) vertices=other.vertices;
        return *this;
    }
    Octagon& operator=(Octagon&& other) noexcept {
        if (this!=&other) vertices=std::move(other.vertices);
        return *this;
    }

    Figure* clone() const override {
        return new Octagon(*this);
    }

    bool operator==(const Figure& o) const override {
        const Octagon* h = dynamic_cast<const Octagon*>(&o);
        if (!h) return false;
        for (int i=0;i<8;i++){
            if (fabs(vertices[i].x - h->vertices[i].x)>1e-9 ||
                fabs(vertices[i].y - h->vertices[i].y)>1e-9) return false;
        }
        return true;
    }

    std::pair<double,double> center() const override {
        return polygonCenter(vertices);
    }

    void print(std::ostream &os) const override {
        os<<"Octagon: ";
        for (auto &p: vertices) {
            os<<"("<<p.x<<","<<p.y<<") ";
        }
    }

    void read(std::istream &is) override {
        for (int i=0;i<8;i++){
            is>>vertices[i].x>>vertices[i].y;
        }
    }

    double area() const override {
        return polygonArea(vertices);
    }
};