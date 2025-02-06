#ifndef PMERGELIST_HPP
#define PMERGELIST_HPP

#include <deque>

class PmergeDeque {
  public:
    PmergeDeque();

    PmergeDeque(const PmergeDeque &rhs);
    PmergeDeque &operator=(const PmergeDeque &rhs);

    PmergeDeque(PmergeDeque &&rhs) noexcept;
    PmergeDeque &operator=(PmergeDeque &&rhs) noexcept;

    ~PmergeDeque();

  public:
    std::deque<int> sort(int size, char **args) const;
    void printSeq(const std::deque<int> &deq, int max_print) const;

  private:
    std::deque<std::size_t> _generateJacob(std::size_t n) const;
    std::deque<int> _fordJohnsonSort(const std::deque<int> &deq) const;

  private:
    bool _parseInputDeque(int size, char **args, std::deque<int> &deq) const;
    int _toInt(char *str) const;
};

#endif // !PMERGELIST_HPP
