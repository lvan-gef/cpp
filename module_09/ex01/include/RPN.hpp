#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>

class RPN {
public:
    explicit RPN(char **argv);

    RPN(const RPN &rhs);
    RPN &operator=(const RPN &rhs);

    RPN(RPN && rhs) noexcept;
    RPN &operator=(RPN && rhs) noexcept;

    void result();
    ~RPN();

private:
    std::string _input;
    std::stack<float> _data;
};

#endif // !RPN_HPP
