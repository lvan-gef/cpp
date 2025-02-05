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
    struct Pair {
        int small;
        int large;

        Pair(int a, int b);
    };

  private:
    static std::deque<std::size_t> generate_jacob(std::size_t n);
    static void insert(std::deque<int> &chain, int element, std::size_t hint);
    std::deque<int> ford_johnson_sort(const std::deque<int> &arr) const;

  private:
    bool _parse_input_deque(int size, char **args, std::deque<int> &vec);
    int _toInt(char *str);
};

#endif // !PMERGELIST_HPP
