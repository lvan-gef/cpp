#ifndef PMERGEMEARRAY_HPP
#define PMERGEMEARRAY_HPP

#include <array>
#include <iostream>

class PmergeMeArray {
  public:
    PmergeMeArray();

    PmergeMeArray(const PmergeMeArray &rhs);
    PmergeMeArray &operator=(const PmergeMeArray &rhs);

    PmergeMeArray(PmergeMeArray &&rhs) noexcept;
    PmergeMeArray &operator=(PmergeMeArray &&rhs) noexcept;

    ~PmergeMeArray();

  private:
    // std::array<int, >;
};

#endif // !PMERGEMEARRAY_HPP
