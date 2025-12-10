#include "modem.hpp"

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
        double d00 = std::abs(input_signal[i] - std::complex<double>(1.0, 1.0));
        double d10 = std::abs(input_signal[i] - std::complex<double>(-1.0, 1.0));
        double d01 = std::abs(input_signal[i] - std::complex<double>(1.0, -1.0));
        double d11 = std::abs(input_signal[i] - std::complex<double>(-1.0, -1.0));

        double min_dist = std::min(std::min(d00, d10), std::min(d01, d11));
        
        if (min_dist == d00 || min_dist == d01) {
            output_bits[2 * i] = 0;
        } else {
            output_bits[2 * i] = 1;
        }

        if (min_dist == d00 || min_dist == d10) {
            output_bits[2 * i + 1] = 0;
        } else {
            output_bits[2 * i + 1] = 1;
        }
    }

    return output_bits;
}
