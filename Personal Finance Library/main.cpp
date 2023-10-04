//
//  main.cpp
//  Personal Finance Library
//
//  Created by Andrie on 10/4/23.
//

#include <iostream>
#include <cmath>
#include <random>

class Option {
public:
    bool isCall;
    long double stock_price;
    long double exercise_price;
    long double time_to_expiration; // In days
    long double implied_volatility;
    long double risk_free_rate; // annualized
    
    long double normal_cdf(double mean, double x, double stdev) {
        return 0.5L * (1.0L + std::erf((x - mean) / (stdev * std::sqrt(2.0L))));
    }
    
    double calculateBlackScholes() {
        long double expiration_in_years = time_to_expiration / 365.0;
        long double volatility_factor = implied_volatility * std::sqrt(expiration_in_years);
        
        long double d1 = (std::log(stock_price / exercise_price) +
                     (risk_free_rate + 0.5 * std::pow(implied_volatility, 2)) * expiration_in_years) / volatility_factor;
        long double d2 = d1 - volatility_factor;
        
        std::cout << d1 << std::endl;
        std::cout << d2 << std::endl;
        
        long double call_value = stock_price * normal_cdf(0.0, d1, 1.0) -
                            (exercise_price / (std::exp(risk_free_rate * (expiration_in_years)))) * normal_cdf(0.0, d2, 1.0);
//        double call_price = stock_price * std::normal_distribution<double>(0, d1);
        return call_value;
        
    }
};


int main(int argc, const char * argv[]) {
//    std::normal_distribution<double> distribution(0.0, 1.0);
    Option test;
    
    test.stock_price = 62.0;
    test.exercise_price = 60.0;
    test.time_to_expiration = 40;
    test.implied_volatility = 0.32;
    test.risk_free_rate = 0.04;
    
    std::cout << test.calculateBlackScholes();
    
    return 0;
}


