#ifndef PMERGEMEDEQUE_HPP
#define PMERGEMEDEQUE_HPP

#include <cstdint>
#include <deque>
#include <chrono>

class PmergeMeDeque {
  public:
    explicit PmergeMeDeque(int argc, char **argv);

    PmergeMeDeque(const PmergeMeDeque &rhs);
    PmergeMeDeque &operator=(const PmergeMeDeque &rhs);

    PmergeMeDeque(PmergeMeDeque &&rhs) noexcept;
    PmergeMeDeque &operator=(PmergeMeDeque &&rhs) noexcept;

    ~PmergeMeDeque();

public:
    void sortIt();

  private:
    std::deque<std::uint32_t> _data;
    std::chrono::time_point<std::chrono::high_resolution_clock> _start;
    std::chrono::time_point<std::chrono::high_resolution_clock> _end;
};

#endif // !PMERGEMEDEQUE_HPP
