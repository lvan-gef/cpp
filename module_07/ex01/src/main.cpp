#include "../include/iter.hpp"
#include <vector>


void ft_tolower(char &arr) {
    arr = std::tolower(static_cast<unsigned char>(arr));
}

void ft_toupper(char &arr) {
    arr = std::toupper(static_cast<unsigned char>(arr));
}

void ft_nana(int &arr) {
    arr = arr * 2;
}

int main() {
    char a[] = {'A', 'B', 'C'};

    std::cout << "Original:" << "\n\ta[0]: " << a[0] << "\n\ta[1]: " << a[1]
              << "\n\ta[2]: " << a[2] << std::endl
              << std::endl;

    iter(a, 1000, ft_tolower);

    std::cout << "Changed:" << "\n\ta[0]: " << a[0] << "\n\ta[1]: " << a[1]
              << "\n\ta[2]: " << a[2] << std::endl
              << std::endl;

    std::vector<int> b = {1, 2, 3, 4};
    iter(b.data(), -1, ft_nana);
}
