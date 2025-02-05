#ifndef PMERGELIST_HPP
#define PMERGELIST_HPP

#include <deque>

class PmergeDeque {
  public:
    PmergeDeque() = default;

    PmergeDeque(const PmergeDeque &rhs) = default;
    PmergeDeque &operator=(const PmergeDeque &rhs) = default;

    PmergeDeque(PmergeDeque &&rhs) noexcept = default;
    PmergeDeque &operator=(PmergeDeque &&rhs) noexcept = default;

    ~PmergeDeque() = default;

  public:
    void sort(int size, char **args);

  private:
    std::deque<std::size_t> _generateJacob(std::size_t n) const;
    std::deque<int> _fordJohnsonSort(const std::deque<int> &deq) const;

  private:
    bool _parseInputDeque(int size, char **args, std::deque<int> &deq);
    int _toInt(char *str) const;
    void _printSeq(const std::deque<int> &deq, std::size_t max_print);
};

#endif // !PMERGELIST_HPP
