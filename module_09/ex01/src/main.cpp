#include "../include/RPN.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Expect at least 1 argument" << '\n';
        return 1;
    }

    RPN rpn(argc, argv);
}
