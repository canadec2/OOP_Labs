#include "figure.h"

std::ostream& operator<<(std::ostream &os, const Figure &fig) {
    fig.print(os);
    return os;
}

std::istream& operator>>(std::istream &is, Figure &fig) {
    fig.read(is);
    return is;
}

double polygonArea(const std::vector<Point>& pts) {
    double A=0;
    int n=(int)pts.size();
    for (int i=0;i<n;i++){
        int j=(i+1)%n;
        A += pts[i].x*pts[j].y - pts[j].x*pts[i].y;
    }
    return std::fabs(A)*0.5;
}

std::pair<double,double> polygonCenter(const std::vector<Point>& pts) {
    double cx=0,cy=0;
    for (auto &p: pts) {
        cx+=p.x; cy+=p.y;
    }
    cx/=pts.size();
    cy/=pts.size();
    return {cx,cy};
}