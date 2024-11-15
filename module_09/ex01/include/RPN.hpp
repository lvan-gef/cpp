#ifndef RPN_HPP
#define RPN_HPP

#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <stack>
#include <stdexcept>
#include <string>
#include <utility>

class RPN {
  public:
    RPN();

    RPN(const RPN &rhs);
    RPN &operator=(const RPN &rhs);

    RPN(RPN &&rhs) noexcept;
    RPN &operator=(RPN &&rhs) noexcept;

    ~RPN();

  public:
    void result(const std::string &arg);

  public:
    class Error : public std::runtime_error {
      public:
        explicit Error(const std::string &msg);
    };

  private:
    std::stack<float> _data;

  private:
    static constexpr bool _isOperator(char c) noexcept;
    void _addNbr(const std::string &arg);
    void _calc(char op);
};

#endif // !RPN_HPP
