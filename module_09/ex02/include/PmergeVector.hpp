#ifndef PMERGEVECTOR_HPP
#define PMERGEVECTOR_HPP

#include <vector>

class PmergeVector {
  public:
    PmergeVector() = default;

    PmergeVector(const PmergeVector &rhs) = default;
    PmergeVector &operator=(const PmergeVector &rhs) = default;

    PmergeVector(PmergeVector &&rhs) noexcept = default;
    PmergeVector &operator=(PmergeVector &&rhs) noexcept = default;

    ~PmergeVector() = default;

  public:
    void sort(int size, char **args);

  private:
    struct Pair {
        int small;
        int large;

        Pair(int a, int b);
    };

  private:
    static std::vector<std::size_t> generate_jacob(std::size_t n);
    static void insert(std::vector<int> &chain, int element, std::size_t hint);
    std::vector<int> ford_johnson_sort(const std::vector<int> &arr) const;

  private:
    bool _parse_input_vector(int size, char **args, std::vector<int> &vec);
    int _toInt(char *str);
};

#endif // !PMERGEVECTOR_HPP
