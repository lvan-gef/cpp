#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>

class RPN {
public:
    explicit RPN(int argc, char **argv);

    RPN(const RPN &rhs);
    RPN &operator=(const RPN &rhs);

    RPN(RPN && rhs) noexcept;
    RPN &operator=(RPN && rhs) noexcept;

    ~RPN();
};

#endif // !RPN_HPP
