#include "../include/RPN.hpp"

RPN::RPN() {
    std::cout << std::fixed;
    std::cout.precision(4);
}

RPN::RPN(const RPN &rhs) : _data(rhs._data) {
}

RPN &RPN::operator=(const RPN &rhs) {
    if (this != &rhs) {
        _data = rhs._data;
    }

    return *this;
}

RPN::RPN(RPN &&rhs) noexcept : _data(std::move(rhs._data)){
}

RPN &RPN::operator=(RPN &&rhs) noexcept {
    if (this != &rhs) {
        _data = std::move(rhs._data);
    }

    return *this;
}

void RPN::result(const std::string &arg) {
    auto current = arg.begin();
    auto next = arg.begin();
    const auto end = arg.end();

    while (next != end) {
        next = std::find(current, end, ' ');
        size_t dis = std::distance(current, next);

        if (dis > 2) {
            throw RPN::Error("Error: Invalid input");
        } else if (dis == 2) {
            try {
                if (*current != '-') {
                    throw RPN::Error("Error: input to high. Must be lower then 10");
                }
                _addNbr(std::string(current, next));
            } catch (RPN::Error &e) {
                throw;
            }
        } else {
            if (_isOperator(*current)) {
                try {
                    _calc(*current);
                } catch (RPN::Error &e) {
                    throw;
                }
            } else {
                try {
                    _addNbr(std::string(current, next));
                } catch (RPN::Error &e) {
                    throw;
                }
            }
        }

        if (next != end) {
            current = next + 1;
        }
    }

    if (_data.size() != 1) {
        throw RPN::Error("Error: Expect 1 element on stack got: " + std::to_string(_data.size()));
    }

    std::cout << _data.top() << '\n';
}

RPN::~RPN() {
}

// private
constexpr bool RPN::_isOperator(char c) noexcept {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

void RPN::_calc(char op) {
    if (_data.size() < 2) {
        throw RPN::Error("Error: Not enough elements on the stack");
    }

    const float lastElem = _data.top();
    _data.pop();

    const float secondLastElem = _data.top();
    _data.pop();

    switch (op) {
        case '+':
            _data.push(secondLastElem + lastElem);
            return;
        case '-':
            _data.push(secondLastElem - lastElem);
            return;
        case '*':
            _data.push(secondLastElem * lastElem);
            return;
        case '/':
            if (lastElem == 0) {
                throw RPN::Error("Error: div by zero");
            }

            _data.push(secondLastElem / lastElem);
            return;
        default:
            throw RPN::Error("Error: invalid operator");
    }
}

void RPN::_addNbr(const std::string &arg) {
    try {
        _data.emplace(std::stof(arg));
    } catch (std::invalid_argument &) {
        throw RPN::Error("Error: invalid input not a int");
    } catch (std::out_of_range &) {
        throw RPN::Error("Error: int did under or overflowed");
    } catch (...) {
        throw RPN::Error("Error: Unkown error");
    }
}

RPN::Error::Error(const std::string &msg) : std::runtime_error(msg) {
}
