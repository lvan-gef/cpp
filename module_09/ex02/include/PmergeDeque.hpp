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
  private:
    static std::deque<std::size_t> generateJacob(std::size_t n);
    static void insert(std::deque<int> &chain, int element, std::size_t hint);
    std::deque<int> fordJohnsonSort(const std::deque<int> &deq) const;

  private:
    bool _parseInputDeque(int size, char **args, std::deque<int> &deq);
    int _toInt(char *str);
    void printSeq(const std::deque<int> &deq, std::size_t max_print);
};

#endif // !PMERGELIST_HPP
