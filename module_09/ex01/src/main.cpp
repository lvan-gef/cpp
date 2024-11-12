#include "../include/RPN.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Expect 1 argument got: " << argc - 1 << '\n';
        return 1;
    }

    RPN rpn; // make input std::string
    try {
        rpn.result(argv[1]);
    } catch (RPN::Error &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
