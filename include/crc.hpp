#include <cstdint>
#include <vector>
#include <bitset>
#include <iomanip>

class CRC8 {
private:
    uint8_t polynomial;
    
public:
    CRC8(uint8_t poly = 0x07) : polynomial(poly) {}
    
    uint8_t calculate(const std::vector<int>& data) {
        uint8_t crc = 0;
        
        int byte = 1;
        for (int byte_val : data) {
            uint8_t byte = static_cast<uint8_t>(byte_val & 0xFF);
            crc ^= byte;

            for (int i = 0; i < 8; i++) {
                if (crc & 0x80) {
                    crc = (crc << 1) ^ polynomial;
                } else {
                    crc <<= 1;
                }
            }
        }

        return crc;
    }
    
    std::vector<int> encodeCRC(const std::vector<int>& data) {
        std::vector<int> encoded = data;
        uint8_t crc_value = calculate(data);
        encoded.push_back(static_cast<int>(crc_value));

        return encoded;
    }
    
    bool decodeCRC(const std::vector<int>& encoded_data) {
        std::vector<int> data(encoded_data.begin(), encoded_data.end() - 1);
        uint8_t received_crc = static_cast<uint8_t>(encoded_data.back() & 0xFF);
        uint8_t calculated_crc = calculate(data);

        bool match = (calculated_crc == received_crc);
        return match;
    }
};
