#include "../include/RPN.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Expect 1 argument got: " << argc - 1 << '\n';
        return 1;
    }

    RPN rpn(argv);  // make input std::string
    rpn.result();
}
