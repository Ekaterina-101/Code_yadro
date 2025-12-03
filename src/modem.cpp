#include "../include/modem.hpp"
#include "../include/noise.hpp"
#include <vector>
#include <cmath>

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

std::vector<std::complex<double>> QPSKmod(const std::vector<int>& input_bits) {
    size_t length = input_bits.size() / 2;
    std::vector<std::complex<double>> modulated_signal(length);

    double norm = 1.0 / std::sqrt(2.0);
    
    for (size_t i = 0; i < length; i++) {
        modulated_signal[i].real((1 - 2 * input_bits[2 * i]) * norm);
        modulated_signal[i].imag((1 - 2 * input_bits[2 * i + 1]) * norm);
    }

    return modulated_signal;
}

std::vector<int> QPSKdemod(const std::vector<std::complex<double>>& input_signal) {
    size_t length = input_signal.size();
    std::vector<int> output_bits(length * 2);

    for (size_t i = 0; i < length; i++) {
        if (input_signal[i].real() < 0) {
            output_bits[2 * i] = 1;
        } else {
            output_bits[2 * i] = 0;
        }

        if (input_signal[i].imag() < 0) {
            output_bits[2 * i + 1] = 1;
        } else {
            output_bits[2 * i + 1] = 0;
        }
    }

    return output_bits;
}
