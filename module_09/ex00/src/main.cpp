#include "../include/BitcoinExchange.hpp"
#include "../include/FileHandler.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "btc expect 1 argument got: " << argc - 1 << '\n';
        return 1;
    }

    (void)argv;
    FileHandler fd = FileHandler("db/data.csv");
    while (fd.isEof() != true) {
        ExchangeData ed = fd.gnl();
        std::cout << ed.date << " " << ed.value << '\n';
    }

    return 0;
}
