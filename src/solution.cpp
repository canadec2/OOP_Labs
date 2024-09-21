#include "../include/solution.h"
#include <stack>
#include <string>

bool isValid(const std::string& s) {
    std::stack<char> stack;
    
    for (char c : s) {
        if (c == '(') {
            stack.push(c);
        } else {
            if (stack.empty()) {
                return false;
            }
            stack.pop();
        }
    }
    
    return stack.empty();
}