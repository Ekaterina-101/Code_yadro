#include "../include/noise.hpp"
#include <vector>
#include <random>
#include <iostream>

std::vector<double> BSC(double p, std::vector<double>& word) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    
    std::vector<double> result = word;
    
    for (std::size_t i = 0; i < result.size(); i++) {
        double random_value = dist(gen);
        
        if (random_value < p) {
            result[i] *= -1;
        }
    }
    
    return result;
}
