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
    static std::vector<std::size_t> generateJacob(std::size_t n);
    std::vector<int> fordJohnsonSort(const std::vector<int> &arr) const;

  private:
    bool _parseInputVector(int size, char **args, std::vector<int> &vec);
    int _toInt(char *str);
    void printSeq(const std::vector<int> &vec, std::size_t max_print);
};

#endif // !PMERGEVECTOR_HPP
