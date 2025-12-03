#include "../include/noise.hpp"
#include <vector>
#include <random>
#include <iostream>
#include <cmath>

std::vector<std::complex<double>> AWGN_Q(double SNR, std::vector<std::complex<double>>& word) {

    double b = 0.5 * std::pow(10.0, -SNR/10.0);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(0.0, b/2.0);

    std::vector<std::complex<double>> res = word;

    for (std::size_t i = 0; i < word.size(); i++) {
        res[i].real(res[i].real() + dist(gen));
        res[i].imag(res[i].imag() + dist(gen));
    }

    return res;
}

std::vector<double> AWGN_B(double SNR, std::vector<double>& word) {

    double b = 0.5 * std::pow(10.0, -SNR/10.0);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(0.0, b);

    std::vector<double> res = word;

    for (std::size_t i = 0; i < word.size(); i++) {
        res[i] += dist(gen);
    }

    return res;
}

// int main() {
//     std::vector<double> w = {1, -1, 1, -1, 1, 1, 1};
//     std::vector<double> res = AWGN_B(0.0001, w);
//     std::cout << "word" << std::endl;
//     for (std::size_t i = 0; i < res.size(); i++) {
//         std::cout << w[i] << " ";
//     }
//     std::cout << std::endl;

//     std::cout << "word after AWGN_B" << std::endl;
//     for (std::size_t i = 0; i < res.size(); i++) {
//         std::cout << res[i] << " ";
//     }
//     std::cout << std::endl;
// }