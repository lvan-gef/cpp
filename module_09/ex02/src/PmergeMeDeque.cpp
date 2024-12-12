#include "../include/PmergeMeDeque.hpp"
#include <climits>
#include <cstdint>
#include <iostream>
#include <stdexcept>

PmergeMeDeque::PmergeMeDeque(int argc, char **argv) : _start(std::chrono::high_resolution_clock::now()), _end(std::chrono::high_resolution_clock::now()) {
    int index = 1; // first arg is program so skip it

    while (index < argc) {
        char *endptr = nullptr;

        long int result = strtol(argv[index], &endptr, 10);
        if (*endptr != '\0') {
            throw std::invalid_argument("Input was not a positive interger");
        }

        if (result < 0 or result > INT_MAX) {
            throw std::invalid_argument("Input was not a positive interger");
        }

        _data.push_back(static_cast<std::uint32_t>(result));
        index++;
    }
}

PmergeMeDeque::PmergeMeDeque(const PmergeMeDeque &rhs) : _data(rhs._data), _start(rhs._start), _end(rhs._end) {
}

PmergeMeDeque &PmergeMeDeque::operator=(const PmergeMeDeque &rhs) {
    if (this != &rhs) {
        _data = rhs._data;
        _start = rhs._start;
        _end = rhs._end;
    }

    return *this;
}

PmergeMeDeque::PmergeMeDeque(PmergeMeDeque &&rhs) noexcept
    : _data(std::move(rhs._data)), _start(rhs._start), _end(rhs._end) {
}

PmergeMeDeque &PmergeMeDeque::operator=(PmergeMeDeque &&rhs) noexcept {
    if (this != &rhs) {
        _data = std::move(rhs._data);
        rhs._data = {};
        _start = rhs._start;
        _end = rhs._end;
    }

    return *this;
}

PmergeMeDeque::~PmergeMeDeque() {
}

void PmergeMeDeque::sortIt() {
    if (_data.size() > 2) {
        std::deque<std::uint32_t> lhs_tmp;
        std::deque<std::uint32_t> rhs_tmp;

        // step one sort pairs
        while (_data.size() > 1) {
            std::uint32_t lhs = _data.front();
            _data.pop_front();

            std::uint32_t rhs = _data.front();
            _data.pop_front();

            if (lhs > rhs) {
                rhs_tmp.push_front(lhs);
                lhs_tmp.push_front(rhs);
            } else {
                rhs_tmp.push_front(rhs);
                lhs_tmp.push_front(lhs);
            }
        }

        if (_data.size() > 0) {
            std::uint32_t lhs = _data.front();
            rhs_tmp.push_front(lhs);
        }

        // step two sort the pairs on the second value of every pair
        while (rhs_tmp.size() > 1) {
            std::uint32_t lhs = rhs_tmp.front();
            rhs_tmp.pop_front();

            std::uint32_t rhs = rhs_tmp.front();
            rhs_tmp.pop_front();
            _data.
        }

        // merge it together i guess
    } else if (_data.size() == 2) {
        if (_data.front() > _data.back()) {
            std::swap(_data.front(), _data.back());
        }
    }

    _end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(_end - _start);
    std::cout << "Sorting duration: " << duration.count() << " us" << '\n';
}
