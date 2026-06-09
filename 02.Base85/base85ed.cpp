#include "base85ed.h"

#include <array>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace base85 {

static const std::array<uint8_t, 85> ALPHABET = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
    'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '!', '#', '$', '%', '&', '(',
    ')', '*', '+', '-', ';', '<', '=', '>', '?', '@', '^', '_', '`', '{', '|', '}', '~'};

int decode_char(uint8_t c) {
    for (int i = 0; i < 85; ++i) {
        if (ALPHABET[i] == c) {
            return i;
        }
    }

    throw std::invalid_argument("Invalid Base85 character");
}

std::vector<uint8_t> encode(const std::vector<uint8_t>& bytes) {
    std::vector<uint8_t> result;

    for (std::size_t i = 0; i < bytes.size(); i += 4) {
        std::size_t block_size = bytes.size() - i;
        if (block_size > 4) {
            block_size = 4;
        }

        uint32_t value = 0;

        for (std::size_t j = 0; j < 4; ++j) {
            value <<= 8;
            if (j < block_size) {
                value |= bytes[i + j];
            }
        }

        uint8_t encoded_block[5];

        for (int j = 4; j >= 0; --j) {
            encoded_block[j] = ALPHABET[value % 85];
            value /= 85;
        }

        std::size_t chars_to_write = block_size + 1;
        result.insert(result.end(), encoded_block, encoded_block + chars_to_write);
    }

    return result;
}

std::vector<uint8_t> decode(const std::vector<uint8_t>& encoded) {
    std::vector<uint8_t> result;

    for (std::size_t i = 0; i < encoded.size(); i += 5) {
        std::size_t block_size = encoded.size() - i;
        if (block_size > 5) {
            block_size = 5;
        }

        if (block_size == 1) {
            throw std::invalid_argument("Invalid Base85 block size");
        }

        uint32_t value = 0;

        for (std::size_t j = 0; j < 5; ++j) {
            value *= 85;

            if (j < block_size) {
                value += decode_char(encoded[i + j]);
            } else {
                value += 84;
            }
        }

        uint8_t decoded_block[4];

        for (int j = 3; j >= 0; --j) {
            decoded_block[j] = value & 0xFF;
            value >>= 8;
        }

        std::size_t bytes_to_write = block_size - 1;
        result.insert(result.end(), decoded_block, decoded_block + bytes_to_write);
    }

    return result;
}

} // namespace base85
