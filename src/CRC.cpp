// #include <iostream>
// #include <cstdint>
// #include <vector>
// #include <bitset>
// #include <iomanip>

// class CRC8 {
// private:
//     uint8_t polynomial;
    
//     void print_step(const char* description, uint8_t value) {
//         std::cout << "   " << description << ": 0x" << std::hex << (int)value 
//                   << " (" << std::bitset<8>(value) << ")" << std::dec;
//     }
    
// public:
//     CRC8(uint8_t poly = 0x07) : polynomial(poly) {
//         std::cout << "Инициализация CRC8 с полиномом: 0x" 
//                   << std::hex << (int)poly 
//                   << " (" << std::bitset<8>(poly) << ")" << std::dec << std::endl;
//     }
    
//     // КОДЕР: вычисляет CRC для данных (vector<int>)
//     uint8_t calculate(const std::vector<int>& data) {
//         uint8_t crc = 0;
        
//         std::cout << "\n=== Вычисление CRC ===" << std::endl;
//         std::cout << "Начальное значение CRC: 0x00 (" 
//                   << std::bitset<8>(crc) << ")" << std::endl;
        
//         int byte_num = 1;
//         for (int byte_val : data) {
//             // Преобразуем int в uint8_t (берем только младшие 8 бит)
//             uint8_t byte = static_cast<uint8_t>(byte_val & 0xFF);
            
//             std::cout << "\n--- Обработка байта " << byte_num++ 
//                       << ": 0x" << std::hex << (int)byte 
//                       << " (" << std::bitset<8>(byte) << ")" << std::dec << " ---" << std::endl;
            
//             std::cout << "1. XOR с байтом данных:" << std::endl;
//             print_step("Текущий CRC", crc);
//             std::cout << std::endl;
//             print_step("Байт данных", byte);
//             std::cout << std::endl;
            
//             crc ^= byte;
//             print_step("Результат XOR", crc);
//             std::cout << std::endl;
            
//             std::cout << "2. Обработка 8 битов:" << std::endl;
//             for (int i = 0; i < 8; i++) {
//                 std::cout << "   Шаг " << i + 1 << ": ";
                
//                 if (crc & 0x80) {
//                     std::cout << "старший бит = 1" << std::endl;
//                     print_step("   До сдвига", crc);
//                     std::cout << std::endl;
//                     print_step("   Полином", polynomial);
//                     std::cout << std::endl;
                    
//                     crc = (crc << 1) ^ polynomial;
                    
//                     print_step("   После (crc << 1) ^ poly", crc);
//                     std::cout << std::endl;
//                 } else {
//                     std::cout << "старший бит = 0" << std::endl;
//                     print_step("   До сдвига", crc);
//                     std::cout << std::endl;
                    
//                     crc <<= 1;
                    
//                     print_step("   После crc << 1", crc);
//                     std::cout << std::endl;
//                 }
//             }
            
//             std::cout << "3. Итог после байта: ";
//             print_step("CRC", crc);
//             std::cout << std::endl;
//         }
        
//         std::cout << "\nИтоговое значение CRC: 0x" 
//                   << std::hex << (int)crc << std::dec 
//                   << " (" << std::bitset<8>(crc) << ")" << std::endl;
        
//         return crc;
//     }
    
//     // КОДЕР: добавляет CRC к данным (vector<int>)
//     std::vector<int> encode(const std::vector<int>& data) {
//         std::cout << "\n\n=== КОДИРОВАНИЕ (Отправитель) ===" << std::endl;
//         std::cout << "Исходные данные: ";
//         for (size_t i = 0; i < data.size(); i++) {
//             std::cout << "0x" << std::hex << (data[i] & 0xFF);
//             if (i != data.size() - 1) std::cout << ", ";
//         }
//         std::cout << std::dec << std::endl;
        
//         std::vector<int> encoded = data;
//         uint8_t crc_value = calculate(data);
//         encoded.push_back(static_cast<int>(crc_value));
        
//         std::cout << "\nЗакодированные данные (данные + CRC): ";
//         for (size_t i = 0; i < encoded.size(); i++) {
//             std::cout << "0x" << std::hex << (encoded[i] & 0xFF);
//             if (i != encoded.size() - 1) std::cout << ", ";
//         }

// std::cout << std::dec << std::endl;
        
//         return encoded;
//     }
    
//     // ДЕКОДЕР: проверяет данные с CRC (vector<int>)
//     bool decode(const std::vector<int>& encoded_data) {
//         std::cout << "\n\n=== ДЕКОДИРОВАНИЕ (Получатель) ===" << std::endl;
        
//         if (encoded_data.empty()) {
//             std::cout << "Ошибка: пустые данные!" << std::endl;
//             return false;
//         }
        
//         std::cout << "Полученные данные: ";
//         for (size_t i = 0; i < encoded_data.size(); i++) {
//             std::cout << "0x" << std::hex << (encoded_data[i] & 0xFF);
//             if (i != encoded_data.size() - 1) std::cout << ", ";
//         }
//         std::cout << std::dec << std::endl;
        
//         // Отделяем данные от CRC
//         std::vector<int> data(encoded_data.begin(), encoded_data.end() - 1);
//         uint8_t received_crc = static_cast<uint8_t>(encoded_data.back() & 0xFF);
        
//         std::cout << "\n1. Отделяем данные от CRC:" << std::endl;
//         std::cout << "   Данные: ";
//         for (size_t i = 0; i < data.size(); i++) {
//             std::cout << "0x" << std::hex << (data[i] & 0xFF);
//             if (i != data.size() - 1) std::cout << ", ";
//         }
//         std::cout << std::dec << std::endl;
//         std::cout << "   Полученный CRC: 0x" << std::hex << (int)received_crc 
//                   << " (" << std::bitset<8>(received_crc) << ")" << std::dec << std::endl;
        
//         // Вычисляем CRC для данных
//         std::cout << "\n2. Вычисляем CRC для полученных данных:" << std::endl;
//         uint8_t calculated_crc = calculate(data);
        
//         std::cout << "\n3. Сравнение:" << std::endl;
//         std::cout << "   Полученный CRC: 0x" << std::hex << (int)received_crc 
//                   << " (" << std::bitset<8>(received_crc) << ")" << std::dec << std::endl;
//         std::cout << "   Вычисленный CRC: 0x" << std::hex << (int)calculated_crc 
//                   << " (" << std::bitset<8>(calculated_crc) << ")" << std::dec << std::endl;
        
//         bool match = (calculated_crc == received_crc);
        
//         std::cout << "\n4. Результат проверки: ";
//         if (match) {
//             std::cout << "✓ ДАННЫЕ КОРРЕКТНЫ" << std::endl;
//         } else {
//             std::cout << "✗ ОШИБКА В ДАННЫХ!" << std::endl;
//         }
        
//         return match;
//     }
// };
// int main() {
//     CRC8 crc;
    
//     // Исходные данные как vector<int>
//     std::vector<int> original_data = {0x01, 0x02, 0x03, 0x04};
    
//     // КОДИРОВАНИЕ (отправитель)
//     std::cout << "==========================================" << std::endl;
//     std::cout << "          СИМУЛЯЦИЯ ПЕРЕДАЧИ ДАННЫХ       " << std::endl;
//     std::cout << "==========================================" << std::endl;
    
//     std::vector<int> encoded = crc.encode(original_data);
    
//     // ДЕКОДИРОВАНИЕ (получатель) - без ошибок
//     std::cout << "\n\n==========================================" << std::endl;
//     std::cout << "      СЦЕНАРИЙ 1: Корректные данные      " << std::endl;
//     std::cout << "==========================================" << std::endl;
    
//     bool valid = crc.decode(encoded);
//     std::cout << "\nИтоговый вердикт: " << (valid ? "ДАННЫЕ ЦЕЛЫ" : "ОШИБКА") << std::endl;
    
//     // ДЕКОДИРОВАНИЕ с ошибкой
//     std::cout << "\n\n==========================================" << std::endl;
//     std::cout << "    СЦЕНАРИЙ 2: Данные с ошибкой         " << std::endl;
//     std::cout << "==========================================" << std::endl;
    
//     std::vector<int> corrupted = {0x01, 0x02, 0x03, 0x05, encoded[4]}; // 0x04 -> 0x05
//     std::cout << "Искажаем данные: 0x04 -> 0x05" << std::endl;
//     valid = crc.decode(corrupted);
//     std::cout << "\nИтоговый вердикт: " << (valid ? "ДАННЫЕ ЦЕЛЫ" : "ОШИБКА ОБНАРУЖЕНА") << std::endl;
    
//     // Пример с числами больше 255 (берутся только младшие 8 бит)
//     std::cout << "\n\n==========================================" << std::endl;
//     std::cout << "  СЦЕНАРИЙ 3: Числа больше 255           " << std::endl;
//     std::cout << "==========================================" << std::endl;
    
//     std::vector<int> large_numbers = {256, 257, 258, 259}; // 0x100, 0x101, 0x102, 0x103
//     std::cout << "Данные: 256(0x100), 257(0x101), 258(0x102), 259(0x103)" << std::endl;
//     std::cout << "Будут использованы младшие 8 бит: 0x00, 0x01, 0x02, 0x03" << std::endl;
    
//     std::vector<int> encoded_large = crc.encode(large_numbers);
//     valid = crc.decode(encoded_large);
//     std::cout << "\nИтоговый вердикт: " << (valid ? "ДАННЫЕ ЦЕЛЫ" : "ОШИБКА ОБНАРУЖЕНА") << std::endl;
    
//     return 0;
// }
