#include "crc.hpp"
#include "modem.hpp"
#include "noise.hpp"

#include <iostream>


void printResult(std::vector<int>& input_signal, std::vector<int>& output_signal, double param) {
    int count_err_bit = 0;
    for (int i = 0; i < input_signal.size(); i++) {
        if (input_signal[i] != output_signal[i]) {
            count_err_bit++;
        }
    }
    std::cout << std::fixed << std::setprecision(2) << "p/SNR = " << param << std::fixed << std::setprecision(6) << "  BER = " << double(count_err_bit)/input_signal.size() << std::endl;
}

int main() {
    srand(time(0));
    int i = 0;
    std::vector<int> w;
    while (i++ < 100000) {
        int random_bit = rand() % 2;
        w.push_back(random_bit);
    }
    
    CRC8 crc;
    std::vector<int> encoded_CRC = crc.encodeCRC(w);

    std::cout << "\n ----- BPSK + BSC ----- " << std::endl;
    for (int p = 0; p < 100; p += 1) {
        std::vector<double> modulated = BPSKmod(encoded_CRC);
        std::vector<double> noised = BSC(p/100.0, modulated);
        std::vector<int> demodulated = BPSKdemod(noised);

        bool decoded_crc = crc.decodeCRC(demodulated);

        printResult(w, demodulated, p/100.0);
    }

    std::cout << "\n ----- BPSK + AWGN ----- " << std::endl;
    for (double SNR = 4.0; SNR <= 12.0; SNR += 0.05) {
        std::vector<double> modulated = BPSKmod(encoded_CRC);
        std::vector<double> noised = AWGN_B(SNR, modulated);
        std::vector<int> demodulated = BPSKdemod(noised);

        bool decoded_crc = crc.decodeCRC(demodulated);

        printResult(w, demodulated, SNR);
    }

    std::cout << "\n ----- QPSK + AWGN ----- " << std::endl;
    for (double SNR = 4.0; SNR <= 12.0; SNR += 0.05) {
        std::vector<std::complex<double>> modulated = QPSKmod(encoded_CRC);
        std::vector<std::complex<double>> noised = AWGN_Q(SNR, modulated);
        std::vector<int> demodulated = QPSKdemod(noised);

        bool CRCdecoded = crc.decodeCRC(demodulated);

        printResult(w, demodulated, SNR);
    }
}
