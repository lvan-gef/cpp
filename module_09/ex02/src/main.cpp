#include "../include/PmergeMe.hpp"
#include "../include/PmergeMeArray.hpp"
#include "../include/PmergeMeDeque.hpp"
#include <stdexcept>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Expect at least 1 argument got: 0" << '\n';
        return 1;
    }

    try {
        PmergeMeDeque pd(argc, argv);
        pd.sortIt();
    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << '\n';
        return 2;
    }

    return 0;
}
