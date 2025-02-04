#ifndef PMERGEME_TPP
#define PMERGEME_TPP

template <typename Container, typename T>
void binary_insert(Container &sorted_list, T value) {
    auto pos = lower_bound(sorted_list.begin(), sorted_list.end(), value);
    sorted_list.insert(pos, value);
}

template <typename Container, typename T>
Container PmergeMe::ford_johnson_sort(Container arr) const {
    if (arr.size() <= 1) {
        return arr;
    }

    Container primary, secondary;
    auto it = arr.begin();
    while (distance(it, arr.end()) > 1) {
        T first = *it, second = *(++it);
        if (first > second) {
            std::swap(first, second);
        }

        primary.push_back(first);
        secondary.push_back(second);
        ++it;
    }

    if (arr.size() % 2 == 1) {
        primary.push_back(*it);
    }

    primary = ford_johnson_sort<Container, T>(primary);

    Container sorted_list = primary;
    for (T value : secondary) {
        binary_insert(sorted_list, value);
    }

    return sorted_list;
}

#endif // PMERGEME_TPP
