#ifndef PmergeMe_TPP
#define PmergeMe_TPP

template <typename T>
void binary_insert(std::vector<T> &sorted_list, T value) {
    auto pos = lower_bound(sorted_list.begin(), sorted_list.end(), value);
    sorted_list.insert(pos, value);
}

template <typename T>
std::vector<T> ford_johnson_sort(std::vector<T> arr) {
    if (arr.size() <= 1) {
        return arr;
    }

    std::vector<std::pair<T, T>> pairs;
    auto it = arr.begin();
    while (distance(it, arr.end()) > 1) {
        T first = *it, second = *(++it);
        pairs.emplace_back(std::min(first, second), std::max(first, second));
        ++it;
    }

    Container primary, secondary;
    for (auto& p : pairs) {
        primary.push_back(p.first);
        secondary.push_back(p.second);
    }

    if (arr.size() % 2 == 1) {
        primary.push_back(*it); // If odd, last element goes into primary
    }

    primary = ford_johnson_sort<Container, T>(primary);

    Container sorted_list = primary;
    for (T value : secondary) {
        binary_insert(sorted_list, value);
    }

    return sorted_list;
}

#endif // !PmergeMe_TPP
