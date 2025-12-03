#include "../include/noise.hpp"
#include <vector>
#include <random>
#include <iostream>
#include <cmath>

struct complex_signal {
    double Re;
    double Im;
};

std::vector<complex_signal> AWGN_Q(double SNR, std::vector<complex_signal>& word) {

    double b = 0.5 * std::pow(10.0, -SNR/10.0);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(0.0, b/2.0);

    std::vector<complex_signal> res = word;

    for (std::size_t i = 0; i < word.size(); i++) {
        res[i].Re += dist(gen);
        res[i].Im += dist(gen);
    }

    return res;
}

std::vector<double> AWGN_B(double SNR, std::vector<double>& word) {

    double b = 0.5 * std::pow(10.0, -SNR/10.0);

    std::cout << b;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(0.0, b);

    std::vector<double> res = word;

    for (std::size_t i = 0; i < word.size(); i++) {
        res[i] += dist(gen);
    }

    return res;
}
