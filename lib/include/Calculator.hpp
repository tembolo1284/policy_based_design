#ifndef Calculator_HPP
#define Calculator_HPP
#include <iostream>
#include <string>

template <typename CalculationPolicy>
class Calculator {
public:
    // Core functionality to perform financial calculations
    double calculate() {
        return CalculationPolicy::calculate();
    }
};

#endif