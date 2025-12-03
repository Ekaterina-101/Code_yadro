#include <vector>
#include <cmath>

std::vector<double> BPSKmod(const std::vector<int>& input_bits);
std::vector<int> BPSKdemod(const std::vector<double>& input_signal);
std::vector<complex> QPSKmod(const std::vector<int>& input_bits);
std::vector<int> QPSKdemod(const std::vector<complex>& input_signal);
