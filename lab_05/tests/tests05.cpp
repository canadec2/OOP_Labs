#include "../src/solution.cpp"
#include "gtest/gtest.h"
#include <string>

TEST(BlockMemResourceTest, AllocateAndDeallocate) {
    BlockMemResource mr(1024);
    void *p1 = mr.allocate(100, alignof(std::max_align_t));
    ASSERT_NE(nullptr, p1);
    mr.deallocate(p1, 100, alignof(std::max_align_t));

    void *p2 = mr.allocate(200, alignof(std::max_align_t));
    ASSERT_NE(nullptr, p2);
}

TEST(BlockMemResourceTest, DeallocateInvalidPointer) {
    BlockMemResource mr(1024);
    void *p = reinterpret_cast<void *>(0xDEADBEEF);
    mr.deallocate(p, 100, alignof(std::max_align_t));
}

TEST(ForwardChainTest, BasicOperations) {
    BlockMemResource mr(1024);
    ForwardChain<int> lst{&mr};

    lst.appendItem(1);
    lst.appendItem(2);
    lst.appendItem(3);

    int count = 0;
    int sum = 0;
    for (int x : lst) {
        sum += x;
        count++;
    }
    ASSERT_EQ(3, count);
    ASSERT_EQ(6, sum);

    lst.cleanUp();
    ASSERT_TRUE(lst.empty());
}

TEST(ForwardChainTest, AppendAndIterate) {
    BlockMemResource mr(1024);
    ForwardChain<int> lst{&mr};

    for (int i = 0; i < 5; ++i) {
        lst.appendItem(i);
    }

    int expected = 0;
    for (int x : lst) {
        ASSERT_EQ(expected, x);
        expected++;
    }
    ASSERT_EQ(5, expected);
}

TEST(ForwardChainTest, CopyConstructor) {
    BlockMemResource mr(1024);
    ForwardChain<int> lst1{&mr};
    lst1.appendItem(10);
    lst1.appendItem(20);

    ForwardChain<int> lst2 = lst1;

    int values[2];
    int idx = 0;
    for (int x : lst2) {
        values[idx++] = x;
    }
    ASSERT_EQ(values[0], 10);
    ASSERT_EQ(values[1], 20);

    {
        lst1.cleanUp();
        lst1.appendItem(100);

        idx = 0;
        for (int x : lst2) {
            if (idx == 0) ASSERT_EQ(x, 10);
            if (idx == 1) ASSERT_EQ(x, 20);
            idx++;
        }
    }
}

TEST(ForwardChainTest, MoveConstructor) {
    BlockMemResource mr(1024);
    ForwardChain<int> lst1{&mr};
    lst1.appendItem(1);
    lst1.appendItem(2);

    ForwardChain<int> lst2 = std::move(lst1);

    int count = 0;
    int arr[2];
    for (int x : lst2) {
        arr[count++] = x;
    }

    ASSERT_EQ(2, count);
    ASSERT_EQ(1, arr[0]);
    ASSERT_EQ(2, arr[1]);
    ASSERT_TRUE(lst1.empty());
}

struct MyStruct {
    int a;
    double b;
    std::string c;

    bool operator==(const MyStruct &other) const {
        return a == other.a && b == other.b && c == other.c;
    }
};

TEST(ForwardChainTest, ComplexType) {
    BlockMemResource mr(1024);
    ForwardChain<MyStruct> lst{&mr};

    lst.appendItem({1, 2.5, "hello"});
    lst.appendItem({2, 3.14, "world"});

    int count = 0;
    MyStruct arr[2];
    for (auto &s : lst) {
        arr[count++] = s;
    }

    ASSERT_EQ(2, count);
    ASSERT_TRUE(arr[0] == (MyStruct{1, 2.5, "hello"}));
    ASSERT_TRUE(arr[1] == (MyStruct{2, 3.14, "world"}));
}