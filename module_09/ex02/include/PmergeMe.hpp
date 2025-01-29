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
    bool _parse_input_list(char **args, std::list<int> &lis);
    bool _parse_input_vector(char **args, std::vector<int> &vec);
};

#endif // !PMERGEME_HPP
