#include "../tester/include/tester.hpp"
#include "../include/iter.hpp"

// void ft_tolower(char &arr) {
//     arr = std::tolower(static_cast<unsigned char>(arr));
// }
//
// void ft_toupper(char &arr) {
//     arr = std::toupper(static_cast<unsigned char>(arr));
// }
//
// void simple_test() {
//     char a[] = {'A', 'B', 'C'};
//
//     std::cout << "Original:" << "\n\ta[0]: " << a[0] << "\n\ta[1]: " << a[1]
//         << "\n\ta[2]: " << a[2] << std::endl
//         << std::endl;
//
//     iter(a, 3, ft_tolower);
//
//     std::cout << "Changed:" << "\n\ta[0]: " << a[0] << "\n\ta[1]: " << a[1]
//         << "\n\ta[2]: " << a[2] << std::endl
//         << std::endl;
//
//     iter(a, 3, ft_toupper);
//     std::cout << "Changed:" << "\n\ta[0]: " << a[0] << "\n\ta[1]: " << a[1]
//         << "\n\ta[2]: " << a[2] << std::endl
//         << std::endl;
// }


int main() {
    // simple_test();

    testIter();
    return 0;
}
