/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MutantStack.tpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/01 17:56:12 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/02 00:04:25 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_TPP
#define MUTANTSTACK_TPP

template <typename T, typename Container>
MutantStack<T, Container>::MutantStack() {}

template <typename T, typename Container>
MutantStack<T, Container>::MutantStack(const MutantStack &rhs)
    : _data(rhs._data) {}

template <typename T, typename Container>
MutantStack<T, Container> &
MutantStack<T, Container>::operator=(const MutantStack &rhs) {
    if (this != &rhs) {
        _data = rhs._data;
    }
    return *this;
}

template <typename T, typename Container>
MutantStack<T, Container>::MutantStack(const MutantStack &&rhs) noexcept
    : _data(std::move(rhs)) {}

template <typename T, typename Container>
MutantStack<T, Container> &
MutantStack<T, Container>::operator=(MutantStack &&rhs) noexcept {
    if (this != &rhs) {
        _data = std::move(rhs._data);
    }
    return *this;
}

template <typename T, typename Container>
T &MutantStack<T, Container>::top() {
    return _data.back();
}

template <typename T, typename Container>
T &MutantStack<T, Container>::top() const {
    return _data.back();
}

template <typename T, typename Container>
bool MutantStack<T, Container>::empty() const {
    return _data.empty();
}

template <typename T, typename Container>
size_t MutantStack<T, Container>::size() const {
    return _data.size();
}

template <typename T, typename Container>
void MutantStack<T, Container>::push(const T &value) {
    _data.push_back(value);
}

template <typename T, typename Container>
void MutantStack<T, Container>::push(T &&value) {
    _data.push_back(std::move(value));
}

template <typename T, typename Container>
void MutantStack<T, Container>::pop() {
    _data.pop_back();
}

template <typename T, class Container>
template <typename... Args>
void MutantStack<T, Container>::emplace(Args &&...args) {
    _data.emplace_back(std::forward<Args>(args)...);
}

template <typename T, class Container>
void MutantStack<T, Container>::swap(MutantStack &rhs) noexcept {
    _data.swap(rhs._data);
}

template <typename T, class Container>
bool MutantStack<T, Container>::operator==(
    const MutantStack<T, Container> &rhs) const {
    return _data == rhs._data;
}

template <typename T, class Container>
bool MutantStack<T, Container>::operator!=(
    const MutantStack<T, Container> &rhs) const {
    return _data != rhs._data;
}

template <typename T, class Container>
bool MutantStack<T, Container>::operator<(
    const MutantStack<T, Container> &rhs) const {
    return _data < rhs._data;
}

template <typename T, class Container>
bool MutantStack<T, Container>::operator<=(
    const MutantStack<T, Container> &rhs) const {
    return _data <= rhs._data;
}

template <typename T, class Container>
bool MutantStack<T, Container>::operator>(
    const MutantStack<T, Container> &rhs) const {
    return _data > rhs._data;
}

template <typename T, class Container>
bool MutantStack<T, Container>::operator>=(
    const MutantStack<T, Container> &rhs) const {
    return _data >= rhs._data;
}

template <typename T, class Container>
typename MutantStack<T, Container>::iterator
MutantStack<T, Container>::begin() {
    return _data.rbegin();
}

template <typename T, class Container>
typename MutantStack<T, Container>::iterator MutantStack<T, Container>::end() {
    return _data.rend();
}

template <typename T, class Container>
typename MutantStack<T, Container>::const_iterator
MutantStack<T, Container>::begin() const {
    return _data.rbegin();
}

template <typename T, class Container>
typename MutantStack<T, Container>::const_iterator
MutantStack<T, Container>::end() const {
    return _data.rend();
}

template <typename T, class Container>
MutantStack<T, Container>::operator Container &() {
    return _data;
}

template <typename T, class Container>
MutantStack<T, Container>::operator const Container &() const {
    return _data;
}

template <typename T, class Container>
void swap(MutantStack<T, Container> &lhs,
          MutantStack<T, Container> &rhs) noexcept {
    lhs.swap(rhs);
}

template <typename T, typename Container>
MutantStack<T, Container>::~MutantStack() {}

#endif // !MUTANTSTACK_HPP
