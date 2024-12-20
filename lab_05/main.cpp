#include "./src/solution.cpp"
#include <iostream>
#include <string>

struct MyStruct {
    int a;
    double b;
    std::string c;
};

int main() {
    BlockMemResource mr(1024);
    ForwardChain<int> intList{&mr};
    ForwardChain<MyStruct> structList{&mr};

    for (int i = 0; i < 10; ++i) {
        intList.appendItem(i);
    }

    for (int x : intList) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    structList.appendItem({42, 0.99, "test"});
    structList.appendItem({-5, 3.14159, "pi"});

    for (const auto &s : structList) {
        std::cout << s.a << " " << s.b << " " << s.c << std::endl;
    }

    return 0;
}