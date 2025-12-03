#include <vector>
#include <cmath>
#include "../include/noise.hpp"

std::vector<double> BPSKmod(const std::vector<int>& input_bits);
std::vector<int> BPSKdemod(const std::vector<double>& input_signal);
std::vector<complex_signal> QPSKmod(const std::vector<int>& input_bits);
std::vector<int> QPSKdemod(const std::vector<complex_signal>& input_signal);
