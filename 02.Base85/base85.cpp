#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "base85ed.h"

std::vector<uint8_t> read_stdin()
{
    std::vector<uint8_t> data;
    char c;

    while (std::cin.get(c)) {
        data.push_back(static_cast<uint8_t>(c));
    }

    return data;
}

void write_stdout(const std::vector<uint8_t>& data)
{
    for (uint8_t byte : data) {
        std::cout.put(static_cast<char>(byte));
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Use -e/--encode or -d/--decode\n";
        return 1;
    }

    std::string mode = argv[1];
    std::vector<uint8_t> input = read_stdin();

    try {
        if (mode == "-e" || mode == "--encode") {
            write_stdout(base85::encode(input));
        } else if (mode == "-d" || mode == "--decode") {
            write_stdout(base85::decode(input));
        } else {
            std::cerr << "Unknown mode\n";
            return 1;
        }
    } catch (const std::exception& error) {
        std::cerr << error.what() << "\n";
        return 1;
    }

    return 0;
}
