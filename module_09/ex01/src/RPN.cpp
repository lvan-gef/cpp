#include "../include/RPN.hpp"

RPN::RPN(char **argv) : _input(argv[1]) {
}

RPN::RPN(const RPN &rhs) {
    (void)rhs;
    std::cout << "Default copy constructor for RPN is called" << '\n';
}

RPN &RPN::operator=(const RPN &rhs) {
    std::cout << "Copy assigment constructor for RPN is called" << '\n';
    if (this != &rhs) {
    }

    return *this;
}

RPN::RPN(RPN &&rhs) noexcept {
    (void)rhs;
    std::cout << "Default move constructor for RPN is called" << '\n';
}

RPN &RPN::operator=(RPN &&rhs) noexcept {
    std::cout << "Move assigment constructor for RPN is called" << '\n';
    if (this != &rhs) {
    }

    return *this;
}

void RPN::result() {
    for (char c : _input) {
        if (std::isdigit(c)) {
            _data.push(std::stof(std::string(1, c)));
         } else if (std::iswspace(c)) {
            continue;
        } else {
            if (_data.size() < 2) {
                std::cerr << "Error: not enough elements on stack" << '\n';
                return;
            }
            if (c == '*') {
                float last = _data.top();
                _data.pop();

                float second_last = _data.top();
                _data.pop();

                _data.emplace(second_last * last);
            } else if (c == '/') {
                float last = _data.top();
                _data.pop();

                float second_last = _data.top();
                _data.pop();

                if (last == 0.0) {
                    std::cerr << "Error: div by zero";
                    return;
                }

                _data.emplace(second_last / last);
            } else if (c == '+') {
                float last = _data.top();
                _data.pop();

                float second_last = _data.top();
                _data.pop();

                _data.emplace(second_last + last);
            } else if (c == '-') {
                float last = _data.top();
                _data.pop();

                float second_last = _data.top();
                _data.pop();

                _data.emplace(second_last - last);
            } else {
                std::cerr << "Error" << '\n';
                return;
            }
        }
    }

    if (_data.size() != 1) {
        std::cerr << "Error: expect 1 value on the stack got: " << _data.size() << '\n';
        std::cerr << "top: " << _data.top() << " then pop" << '\n';
        _data.pop();
        std::cerr << "next top: " << _data.top() << '\n';
    } else {
        std::cout << _data.top() << '\n';
    }
}

RPN::~RPN() {
}
