#include "modem.hpp"

std::vector<double> BPSKmod(const std::vector<int>& input_bits) {
    size_t length = input_bits.size();
    std::vector<double> modulated_signal(length);

    for (size_t i = 0; i < length; i++) {
        modulated_signal[i] = 1 - 2 * input_bits[i];
    }

    return modulated_signal;
}

std::vector<int> BPSKdemod(const std::vector<double>& input_signal) {
    size_t length = input_signal.size();
    std::vector<int> output_bits(length);

    for (size_t i = 0; i < length; i++) {
        if (input_signal[i] < 0) {
            output_bits[i] = 1;
        } else {
            output_bits[i] = 0;
        }
    }

    return output_bits;
}
