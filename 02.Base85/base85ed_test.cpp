#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "base85ed.h"

std::vector<uint8_t> to_bytes(const std::string& s) {
    return std::vector<uint8_t>(s.begin(), s.end());
}

void test_empty() {
    assert(base85::encode(to_bytes("")) == to_bytes(""));
    assert(base85::decode(to_bytes("")) == to_bytes(""));
}

void test_round_trip_text() {
    std::vector<std::string> cases = {"hello", "Hello, world!", "1234567890",
                                      "Base85 encoder and decoder test"};

    for (const std::string& s : cases) {
        auto data = to_bytes(s);
        assert(base85::decode(base85::encode(data)) == data);
    }
}

void test_round_trip_binary() {
    std::vector<uint8_t> data = {0, 1, 2, 3, 4, 5, 10, 13, 127, 128, 200, 255};

    assert(base85::decode(base85::encode(data)) == data);
}

void test_invalid_character() {
    bool exception_was_thrown = false;

    try {
        base85::decode(to_bytes("\""));
    } catch (...) {
        exception_was_thrown = true;
    }

    assert(exception_was_thrown);
}

int main() {
    test_empty();
    test_round_trip_text();
    test_round_trip_binary();
    test_invalid_character();

    std::cout << "All Base85 tests passed\n";

    return 0;
}
