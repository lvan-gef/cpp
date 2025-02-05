#ifndef PMERGELIST_HPP
#define PMERGELIST_HPP

#include <list>

class PmergeList {
  public:
    PmergeList() = default;

    PmergeList(const PmergeList &rhs) = default;
    PmergeList &operator=(const PmergeList &rhs) = default;

    PmergeList(PmergeList &&rhs) noexcept = default;
    PmergeList &operator=(PmergeList &&rhs) noexcept = default;

    ~PmergeList() = default;

  public:
    void sort(int size, char **args);

  private:
    struct Pair {
        int small;
        int large;

        Pair(int a, int b);
    };

  private:
    static std::list<std::size_t> generate_jacob(std::size_t n);
    static void insert(std::list<int> &chain, int element, std::size_t hint);
    std::list<int> ford_johnson_sort(const std::list<int> &arr) const;

  private:
    bool _parse_input_list(int size, char **args, std::list<int> &vec);
    int _toInt(char *str);
};

#endif // !PMERGELIST_HPP
