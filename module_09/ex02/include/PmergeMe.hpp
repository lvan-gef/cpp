#ifndef PMERGEME_HPP
#define PMERGEME_HPP

class PmergeMe {
  public:
    PmergeMe();

    PmergeMe(const PmergeMe &rhs);
    PmergeMe &operator=(const PmergeMe &rhs);

    PmergeMe(PmergeMe &&rhs) noexcept;
    PmergeMe &operator=(PmergeMe &&rhs) noexcept;

    ~PmergeMe();

  private:
    // array
    // vector

};

#endif // !PMERGEME_HPP
