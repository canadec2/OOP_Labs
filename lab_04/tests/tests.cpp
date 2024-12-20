TEST(ExceptionTest, InvalidHexagon) {
    std::vector<Point<int>> invalidPoints{{0, 0}, {1, 1}, {2, 2}};
    ASSERT_THROW(Hexagon<int> hex(invalidPoints), std::invalid_argument);
}

TEST(ExceptionTest, ArrayOutOfBounds) {
    Array<int> arr;
    arr.push_back(10);

    ASSERT_THROW(arr[1], std::out_of_range);
}

TEST(HexagonTest, ValidHexagon) {
    std::vector<Point<int>> points{{0, 0}, {2, 0}, {3, 2}, {2, 4}, {0, 4}, {-1, 2}};
    Hexagon<int> hex(points);

    ASSERT_NEAR(hex.area(), 12.0, 1e-6);
}

TEST(HexagonTest, GeometricCenter) {
    std::vector<Point<int>> points{{0, 0}, {2, 0}, {3, 2}, {2, 4}, {0, 4}, {-1, 2}};
    Hexagon<int> hex(points);

    auto center = hex.geometricCenter();
    ASSERT_EQ(center.x, 1);
    ASSERT_EQ(center.y, 2);
}

TEST(HexagonTest, InvalidHexagon) {
    std::vector<Point<int>> invalidPoints{{0, 0}, {1, 1}, {2, 2}};
    ASSERT_THROW(Hexagon<int> hex(invalidPoints), std::invalid_argument);
}

TEST(IntegrationTest, AddFiguresToArray) {
    Array<std::shared_ptr<Figure<int>>> arr;

    Point<int> a{0, 0}, b{3, 0}, c{0, 4};
    auto triangle = std::make_shared<Triangle<int>>(a, b, c);
    arr.push_back(triangle);

    std::vector<Point<int>> hexPoints{{0, 0}, {2, 0}, {3, 2}, {2, 4}, {0, 4}, {-1, 2}};
    auto hexagon = std::make_shared<Hexagon<int>>(hexPoints);
    arr.push_back(hexagon);

    ASSERT_EQ(arr.size(), 2);

    ASSERT_NEAR(arr[0]->area(), 6.0, 1e-6);
    ASSERT_NEAR(arr[1]->area(), 12.0, 1e-6);
}

TEST(ExceptionTest, OutOfBounds) {
    Array<int> arr;
    arr.push_back(10);

    ASSERT_THROW(arr[1], std::out_of_range);
}

TEST(ExceptionTest, RemoveInvalidIndex) {
    Array<int> arr;
    ASSERT_THROW(arr.remove(0), std::out_of_range);
}
