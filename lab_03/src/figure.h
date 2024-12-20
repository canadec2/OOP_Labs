#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <utility>

struct Point {
    double x,y;
};

class Figure {
public:
    virtual ~Figure() {}
    virtual std::pair<double,double> center() const = 0;
    virtual void print(std::ostream &os) const = 0;
    virtual void read(std::istream &is) = 0;
    virtual double area() const = 0;
    virtual Figure* clone() const = 0;
    virtual bool operator==(const Figure& other) const = 0;
};

std::ostream& operator<<(std::ostream &os, const Figure &fig);
std::istream& operator>>(std::istream &is, Figure &fig);

// Вспомогательные функции объявим здесь, а определим в figure.cpp
double polygonArea(const std::vector<Point>& pts);
std::pair<double,double> polygonCenter(const std::vector<Point>& pts);