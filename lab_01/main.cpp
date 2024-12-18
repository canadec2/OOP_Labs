#include <iostream>
#include "include/solution.h"
#include <stack>
#include <string>



int main() {
    std::string input;
    std::cin >> input;
    std::cout << std::boolalpha << isValid(input) << std::endl;
    return 0;
}