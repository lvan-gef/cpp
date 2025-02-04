#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <list>
#include <vector>

class PmergeMe {
  public:
    PmergeMe() = default;

    PmergeMe(const PmergeMe &rhs) = default;
    PmergeMe &operator=(const PmergeMe &rhs) = default;

    PmergeMe(PmergeMe &&rhs) noexcept = default;
    PmergeMe &operator=(PmergeMe &&rhs) noexcept = default;

    ~PmergeMe() = default;

  public:
    void run_list(int size, char **args);
    void run_vector(int size, char **args);

  private:
    bool _parse_input_list(int size, char **args, std::list<int> &lis);
    bool _parse_input_vector(int size, char **args, std::vector<int> &vec);
    int _toInt(char *str);

  private:
    template <typename Container, typename T>
    Container ford_johnson_sort(Container arr) const;;
};

#include "../templates/PmergeMe.tpp"

#endif // !PMERGEME_HPP
