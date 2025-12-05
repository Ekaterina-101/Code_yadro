#include <vector>
#include <random>
#include <cmath>
#include <complex>

std::vector<std::complex<double>> AWGN_Q(double SNR, std::vector<std::complex<double>>& word);
std::vector<double> AWGN_B(double SNR, std::vector<double>& word);
std::vector<double> BSC(double p, std::vector<double>& word);
