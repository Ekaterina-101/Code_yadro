#include <cstdint>
#include <vector>
#include <bitset>
#include <iomanip>

class CRC8 {
private:
    uint8_t polynomial;
    
public:
    CRC8(uint8_t poly = 0x07);
    uint8_t calculate(const std::vector<int>& data);

    std::vector<int> encodeCRC(const std::vector<int>& data);
    bool decodeCRC(const std::vector<int>& encoded_data);
};
