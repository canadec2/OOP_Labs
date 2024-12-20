#include <iostream>
#include <vector>
#include "src/figure.h"
#include "src/hexagon.h"
#include "src/octagon.h"
#include "src/triangle.h"

int main() {
    std::cout << "Введите количество фигур: ";
    int N; 
    std::cin >> N;

    std::vector<Figure*> figs;
    figs.reserve(N);

    for (int i=0; i<N; i++) {
        std::cout << "Выберите тип фигуры (1=Hexagon, 2=Octagon, 3=Triangle): ";
        int t; 
        std::cin >> t;
        Figure *fig = nullptr;
        switch(t) {
            case 1: fig = new Hexagon(); break;
            case 2: fig = new Octagon(); break;
            case 3: fig = new Triangle(); break;
            default:
                std::cout << "Неизвестный тип\n";
                i--; // повторим попытку
                continue;
        }
        std::cout << "Введите координаты вершин:\n";
        std::cin >> *fig;

        figs.push_back(fig);
    }

    double total_area = 0.0;
    std::cout << "\nРезультаты:\n";
    for (auto f : figs) {
        auto c = f->center();
        double a = f->area();
        std::cout << *f << "\nЦентр: (" << c.first << "," << c.second << ")\n"
                  << "Площадь: " << a << "\n\n";
        total_area += a;
    }

    std::cout << "Суммарная площадь всех фигур: " << total_area << "\n";

    for (auto f : figs) {
        delete f;
    }
    figs.clear();

    return 0;
}