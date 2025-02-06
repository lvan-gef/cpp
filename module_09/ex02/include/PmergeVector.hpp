#ifndef PMERGEVECTOR_HPP
#define PMERGEVECTOR_HPP

#include <vector>

class PmergeVector {
  public:
    PmergeVector();

    PmergeVector(const PmergeVector &rhs);
    PmergeVector &operator=(const PmergeVector &rhs);

    PmergeVector(PmergeVector &&rhs) noexcept;
    PmergeVector &operator=(PmergeVector &&rhs) noexcept;

    ~PmergeVector();

  public:
    std::vector<int> sort(int size, char **args) const;
    void printSeq(const std::vector<int> &vec, int max_print) const;

  private:
    std::vector<std::size_t> _generateJacob(std::size_t n) const;
    std::vector<int> _fordJohnsonSort(const std::vector<int> &arr) const;

  private:
    bool _parseInputVector(int size, char **args, std::vector<int> &vec) const;
    int _toInt(char *str) const;
};

#endif // !PMERGEVECTOR_HPP
