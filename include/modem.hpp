#include <vector>
#include <cmath>
#include <complex>

std::vector<double> BPSKmod(const std::vector<int>& input_bits);
std::vector<int> BPSKdemod(const std::vector<double>& input_signal);

std::vector<std::complex<double>> QPSKmod(const std::vector<int>& input_bits);
std::vector<int> QPSKdemod(const std::vector<std::complex<double>>& input_signal);
