#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include "PmergeDeque.hpp"
#include "PmergeVector.hpp"

class PmergeMe {
  public:
    PmergeMe() = default;

    PmergeMe(const PmergeMe &rhs) = default;
    PmergeMe &operator=(const PmergeMe &rhs) = default;

    PmergeMe(PmergeMe &&rhs) noexcept = default;
    PmergeMe &operator=(PmergeMe &&rhs) noexcept = default;

    ~PmergeMe() = default;

  public:
    void run_vector(int size, char **args);
    void run_deque(int size, char **args);

  private:
    PmergeVector _vec;
    PmergeDeque _deq;
};

#endif // !PMERGEME_HPP
