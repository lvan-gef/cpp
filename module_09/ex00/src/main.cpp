#include "../include/BitcoinExchange.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "btc expect 1 argument got: " << argc - 1 << '\n';
        return 1;
    }

    try {
        BitcoinExchange be("db/data.csv");
        be.getResult(argv[1]);
    } catch (FileHandler::FileError &e) {
        std::cerr << e.what() << '\n';
        return 2;
    }

    return 0;
}
