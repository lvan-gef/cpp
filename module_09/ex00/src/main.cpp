#include "../include/BitcoinExchange.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "btc expect 1 argument got: " << argc - 1 << '\n';
        return 1;
    }

    BitcoinExchange be;
    try {
        be = BitcoinExchange("db/data.csv");
    } catch (FileHandler::FileError &e) {
        std::cerr << e.what() << '\n';
        return 2;
    }

    try {
        be.getResult(argv[1]);
    } catch (BitcoinExchange::BE &e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
