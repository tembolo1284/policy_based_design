#ifndef CalculationPolicies_HPP
#define CalculationPolicies_HPP
#include <iostream>
#include <string>

// CalculationPolicies.h
class PresentValuePolicy {
public:
    static double calculate() {
        // Implement the present value calculation logic
		std::cout << "Hello from PresentValue Policy calculate" << "\n";
		return 1.1;
    }
};

class FutureValuePolicy {
public:
    static double calculate() {
        // Implement the future value calculation logic
		std::cout << "Hello from FutureValue Policy calculate" << "\n";
		return 2.2;
    }
};

class InterestRateConversionPolicy {
public:
    static double calculate() {
        // Implement the interest rate conversion logic
		std::cout << "Hello from IRate Conversion Policy calculate" << "\n";
		return 3.3;
    }
};


#endif