#include "../include/BitcoinExchange.hpp"
#include <stdexcept>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "btc expect 1 argument got: " << argc - 1 << '\n';
        return 1;
    }

    (void)argv;

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

    // FileHandler fd("db/data.csv");
    // while (fd.isEof() != true) {
    //     try {
    //         ExchangeDay ed = fd.gnl();
    //         std::cout << ed.date << " " << ed.value << '\n';
    //     } catch (std::runtime_error &e) {
    //         std::cerr << "Error in runtime: " << e.what() << '\n';
    //         return 2;
    //     } catch (std::invalid_argument &e) {
    //         std::cerr << e.what() << '\n';
    //         return 3;
    //     } catch (FileHandler::FileEOF &) {
    //         break;
    //     }
    // }

    return 0;
}
