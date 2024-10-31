#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <cstddef>
#include <deque>
#include <iostream>

template <typename T, class Container = std::deque<T>>
class MutantStack {
  public:
    using container_type = Container;
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;

    MutantStack() = default;

    MutantStack(const MutantStack &rhs);
    MutantStack &operator=(const MutantStack &rhs);

    MutantStack(const MutantStack &&rhs) noexcept;
    MutantStack &operator=(MutantStack &&rhs) noexcept;

    T &top();
    T &top() const;
    bool empty() const;
    size_t size() const;

    void push(const T &value);
    void push(T &&value);
    void pop();
    template <typename... Args>
    void emplace(Args &&...args);
    void swap(MutantStack &rhs) noexcept;

    bool operator==(const MutantStack &rhs) const;
    bool operator!=(const MutantStack &rhs) const;
    bool operator<(const MutantStack &rhs) const;
    bool operator<=(const MutantStack &rhs) const;
    bool operator>(const MutantStack &rhs) const;
    bool operator>=(const MutantStack &rhs) const;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    // ??  std::swap(std::stack)

    // helper classes
    //  std::uses_allocator<std::stack>

    // subject iterator
    ~MutantStack() = default;

  private:
    std::deque<T> _data;
};

#include "../templates/MutantStack.tpp"

#endif // !MUTANTSTACK_HPP
