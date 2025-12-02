#include <vector>
#include <random>
#include <iostream>
#include <cmath>

struct complex {
    double Re;
    double Im;
};

std::vector<complex> AWGN_Q(double SNR, std::vector<complex>& word) {

    double b = 0.5 * std::pow(10.0, -SNR/10.0);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(0.0, b/2.0);

    std::vector<complex> res = word;

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

int main() {
    std::vector<double> w = {1, -1, 1, -1, 1, 1, 1};
    std::vector<double> res = AWGN_B(12.0, w);
    std::cout << "word" << std::endl;
    for (std::size_t i = 0; i < res.size(); i++) {
        std::cout << w[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "word after AWGN_B" << std::endl;
    for (std::size_t i = 0; i < res.size(); i++) {
        std::cout << res[i] << " ";
    }
    std::cout << std::endl;
}