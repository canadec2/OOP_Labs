#pragma once
#include "figure.h"

class Hexagon : public Figure {
private:
    std::vector<Point> vertices;
public:
    Hexagon():vertices(6){}
    Hexagon(const Hexagon& other):vertices(other.vertices){}
    Hexagon(Hexagon&& other) noexcept : vertices(std::move(other.vertices)){}
    Hexagon& operator=(const Hexagon& other) {
        if (this!=&other) vertices=other.vertices;
        return *this;
    }
    Hexagon& operator=(Hexagon&& other) noexcept {
        if (this!=&other) vertices=std::move(other.vertices);
        return *this;
    }

    Figure* clone() const override {
        return new Hexagon(*this);
    }

    bool operator==(const Figure& o) const override {
        const Hexagon* h = dynamic_cast<const Hexagon*>(&o);
        if (!h) return false;
        for (int i=0;i<6;i++){
            if (fabs(vertices[i].x - h->vertices[i].x)>1e-9 ||
                fabs(vertices[i].y - h->vertices[i].y)>1e-9) return false;
        }
        return true;
    }

    std::pair<double,double> center() const override {
        return polygonCenter(vertices);
    }

    void print(std::ostream &os) const override {
        os<<"Hexagon: ";
        for (auto &p: vertices) {
            os<<"("<<p.x<<","<<p.y<<") ";
        }
    }

    void read(std::istream &is) override {
        for (int i=0;i<6;i++){
            is>>vertices[i].x>>vertices[i].y;
        }
    }

    double area() const override {
        return polygonArea(vertices);
    }
};