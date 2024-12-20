#include <gtest/gtest.h>
#include "../src/figure.h"
#include "../src/hexagon.h"
#include "../src/octagon.h"
#include "../src/triangle.h"
#include <sstream>
#include <cmath>

// Функция для приблизительного сравнения пары double
static void expectNearPair(std::pair<double,double> p1, std::pair<double,double> p2, double eps=1e-6) {
    EXPECT_NEAR(p1.first, p2.first, eps);
    EXPECT_NEAR(p1.second, p2.second, eps);
}

/*
Тесты для Triangle:
- Проверяем площадь равностороннего треугольника.
- Проверяем центр для простого треугольника.
- Проверяем операции сравнения и копирования.
*/

TEST(TriangleTest, AreaEquilateral) {
    Triangle tri;
    std::istringstream iss("0 0 2 0 1 1.732");
    iss >> tri;
    EXPECT_NEAR(tri.area(), 1.732, 1e-3);
}

TEST(TriangleTest, Center) {
    Triangle tri;
    std::istringstream iss("0 0 2 0 0 2");
    iss >> tri;
    auto c = tri.center();
    expectNearPair(c,{0.6666667,0.6666667});
}

TEST(TriangleTest, EqualityAndCopy) {
    Triangle t1, t2;
    std::istringstream iss1("0 0 1 0 0 1");
    std::istringstream iss2("0 0 1 0 0 1");
    iss1 >> t1;
    iss2 >> t2;

    EXPECT_TRUE(t1==t2);

    std::istringstream iss3("0 0 1 0 0 2");
    iss3 >> t2;
    EXPECT_FALSE(t1==t2);

    Triangle t3 = t1;
    EXPECT_TRUE(t1==t3);

    Triangle t4(std::move(t3));
    EXPECT_TRUE(t1==t4);
}

/*
Тесты для Hexagon:
- Проверяем площадь для шестиугольника.
- Проверяем центр.
- Проверяем оператор==
- Проверяем копирование и перемещение.
*/

TEST(HexagonTest, AreaRegularHex) {
    Hexagon h;
    double s = std::sqrt(3)/2;
    std::ostringstream oss;
    oss << "1 0 0.5 " << s << " -0.5 " << s << " -1 0 -0.5 " << -s << " 0.5 " << -s;
    std::istringstream iss(oss.str());
    iss >> h;
    EXPECT_NEAR(h.area(), 2.598, 1e-3);
}

TEST(HexagonTest, CenterCheck) {
    Hexagon h;
    std::istringstream iss("0 0 2 0 2 2 1 3 0 2 0 1");
    iss >> h;
    auto c = h.center();
    expectNearPair(c,{0.8333333,1.3333333});
}

TEST(HexagonTest, EqualityCopyMove) {
    Hexagon h1;
    std::istringstream iss("0 0 1 0 2 1 2 2 1 2 0 1");
    iss >> h1;

    Hexagon h2 = h1;
    EXPECT_TRUE(h1 == h2);

    Hexagon h3(std::move(h2));
    EXPECT_TRUE(h1 == h3);

    std::istringstream iss2("0 0 1 0 2 1 3 2 1 2 0 1");
    iss2 >> h3;
    EXPECT_FALSE(h1 == h3);
}

/*
Тесты для Octagon:
- Проверяем площадь (сложный многоугольник).
- Проверяем центр.
- Проверяем равенство.
*/

TEST(OctagonTest, AreaPositive) {
    Octagon o;
    std::istringstream iss("0 0 2 0 3 1 3 2 2 3 1 3 0 2 -0.5 1");
    iss >> o;
    double A=o.area();
    EXPECT_GT(A,0.0);
}

TEST(OctagonTest, CenterCheck) {
    Octagon o;
    std::istringstream iss("0 0 4 0 5 1 5 2 4 3 2 3 1 2 0 1");
    iss >> o;
    auto c = o.center();
    expectNearPair(c,{2.625,1.5});
}

TEST(OctagonTest, EqualityCheck) {
    Octagon o1, o2;
    std::istringstream iss1("0 0 1 0 2 1 3 1 3 2 2 3 1 3 0 1");
    std::istringstream iss2("0 0 1 0 2 1 3 1 3 2 2 3 1 3 0 1");
    iss1 >> o1;
    iss2 >> o2;
    EXPECT_TRUE(o1 == o2);

    std::istringstream iss3("0 0 1 0 2 1 3 1 3 2 2 3 1 3 0 2");
    iss3 >> o2;
    EXPECT_FALSE(o1 == o2);
}

// Дополнительные тесты на ввод/вывод:

TEST(IOTest, TriangleIO) {
    Triangle t1;
    std::istringstream iss("0 0 1 0 0 1");
    iss >> t1;

    std::ostringstream oss;
    oss << t1;

    Triangle t2;

    std::istringstream iss2("0 0 1 0 0 1");
    iss2 >> t2;
    EXPECT_TRUE(t1==t2);
}

TEST(IOTest, HexagonIO) {
    Hexagon h1;
    std::istringstream iss("0 0 1 0 2 1 2 2 1 2 0 1");
    iss >> h1;

    Hexagon h2;
    std::istringstream iss2("0 0 1 0 2 1 2 2 1 2 0 1");
    iss2 >> h2;

    EXPECT_TRUE(h1==h2);
}

TEST(IOTest, OctagonIO) {
    Octagon o1;
    std::istringstream iss("0 0 4 0 5 1 5 2 4 3 2 3 1 2 0 1");
    iss >> o1;

    Octagon o2;
    std::istringstream iss2("0 0 4 0 5 1 5 2 4 3 2 3 1 2 0 1");
    iss2 >> o2;

    EXPECT_TRUE(o1==o2);
}

// Проверим большое количество фигур, подсчет суммарной площади:

TEST(MassTest, ManyFiguresTotalArea) {
    std::vector<Figure*> figs;
    for (int i=0; i<10; i++){
        Triangle *t = new Triangle();
        std::istringstream iss("0 0 1 0 0 1");
        iss>>*t;
        figs.push_back(t);
    }
    for (int i=0; i<10; i++){
        Hexagon *h = new Hexagon();
        std::istringstream iss("0 0 1 0 2 1 2 2 1 2 0 1");
        iss>>*h;
        figs.push_back(h);
    }
    for (int i=0; i<10; i++){
        Octagon *o = new Octagon();
        std::istringstream iss("0 0 4 0 5 1 5 2 4 3 2 3 1 2 0 1");
        iss>>*o;
        figs.push_back(o);
    }

    double total=0;
    for (auto f : figs) {
        total += f->area();
        delete f;
    }
    figs.clear();
    EXPECT_GT(total,0.0);
}

// Запуск всех тестов
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}