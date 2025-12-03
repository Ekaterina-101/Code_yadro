#include <vector>
#include <random>
#include <iostream>
#include <cmath>

struct complex_signal {
    double Re;
    double Im;
};

std::vector<complex_signal> AWGN_Q(double SNR, std::vector<complex_signal>& word);
std::vector<double> AWGN_B(double SNR, std::vector<double>& word);
std::vector<double> BSC(double p, std::vector<double>& word);
