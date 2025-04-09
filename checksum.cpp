#include <iostream>
#include <vector>
#include <string>

class CRC32 {
private:
    static constexpr uint32_t POLYNOMIAL = 0xEDB88320;
    uint32_t table[256];

    void generateTable() {
        for (uint32_t i = 0; i < 256; i++) {
            uint32_t crc = i;
            for (uint32_t j = 0; j < 8; j++) {
                if (crc & 1)
                    crc = (crc >> 1) ^ POLYNOMIAL;
                else
                    crc >>= 1;
            }
            table[i] = crc;
        }
    }

public:
    CRC32() {
        generateTable();
    }

    uint32_t calculate(const std::string& data) {
        uint32_t crc = 0xFFFFFFFF;
        for (unsigned char byte : data) {
            crc = (crc >> 8) ^ table[(crc ^ byte) & 0xFF];
        }
        return crc ^ 0xFFFFFFFF;
    }
};

int main() {
    CRC32 crc32;
    std::string input;
	std::getline(std::cin, input);
    uint32_t checksum = crc32.calculate(input);
    std::cout << "CRC32: " << std::hex << checksum << std::endl;
    return 0;
}
