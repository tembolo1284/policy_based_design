#ifndef CalculationPolicies_HPP
#define CalculationPolicies_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
#include <stdexcept>

// ===========================================================================
// PresentValuePolicy
// ===========================================================================
// Calculate the present value of a series of future cash flows
// Formula: PV = Σ(CF_t / (1 + r)^t) for t = 1 to n
class PresentValuePolicy {
public:
    static double calculate(double discount_rate, const std::vector<double>& cash_flows) {
        if (cash_flows.empty()) {
            throw std::invalid_argument("Cash flows vector cannot be empty");
        }
        
        if (discount_rate <= -1.0) {
            throw std::invalid_argument("Discount rate must be greater than -1");
        }
        
        std::cout << "PresentValuePolicy: Calculating PV with discount rate " 
                  << discount_rate << " for " << cash_flows.size() 
                  << " cash flows\n";
        
        double present_value = 0.0;
        for (size_t t = 0; t < cash_flows.size(); ++t) {
            double discount_factor = std::pow(1.0 + discount_rate, static_cast<double>(t + 1));
            present_value += cash_flows[t] / discount_factor;
            
            std::cout << "  Period " << (t + 1) << ": CF=" << cash_flows[t] 
                      << ", Discount Factor=" << discount_factor 
                      << ", PV=" << (cash_flows[t] / discount_factor) << "\n";
        }
        
        std::cout << "  Total Present Value: " << present_value << "\n";
        return present_value;
    }
};

// ===========================================================================
// FutureValuePolicy
// ===========================================================================
// Calculate the future value of a present amount
// Formula: FV = PV * (1 + r)^n
class FutureValuePolicy {
public:
    static double calculate(double principal, double interest_rate, int periods) {
        if (principal < 0.0) {
            throw std::invalid_argument("Principal must be non-negative");
        }
        
        if (periods < 0) {
            throw std::invalid_argument("Periods must be non-negative");
        }
        
        if (interest_rate <= -1.0) {
            throw std::invalid_argument("Interest rate must be greater than -1");
        }
        
        std::cout << "FutureValuePolicy: Calculating FV of principal=" << principal
                  << " at rate=" << interest_rate 
                  << " over " << periods << " periods\n";
        
        double future_value = principal * std::pow(1.0 + interest_rate, static_cast<double>(periods));
        
        std::cout << "  Growth Factor: " << std::pow(1.0 + interest_rate, static_cast<double>(periods)) << "\n";
        std::cout << "  Future Value: " << future_value << "\n";
        
        return future_value;
    }
};

// ===========================================================================
// InterestRateConversionPolicy
// ===========================================================================
// Convert nominal interest rate to effective annual rate
// Formula: EAR = (1 + r/n)^n - 1
class InterestRateConversionPolicy {
public:
    static double calculate(double nominal_rate, int compounding_periods) {
        if (compounding_periods <= 0) {
            throw std::invalid_argument("Compounding periods must be positive");
        }
        
        if (nominal_rate <= -1.0) {
            throw std::invalid_argument("Nominal rate must be greater than -1");
        }
        
        std::cout << "InterestRateConversionPolicy: Converting nominal rate=" 
                  << nominal_rate << " with " << compounding_periods 
                  << " compounding periods\n";
        
        double rate_per_period = nominal_rate / static_cast<double>(compounding_periods);
        double effective_rate = std::pow(1.0 + rate_per_period, static_cast<double>(compounding_periods)) - 1.0;
        
        std::cout << "  Rate per period: " << rate_per_period << "\n";
        std::cout << "  Effective Annual Rate: " << effective_rate << "\n";
        
        return effective_rate;
    }
};

#endif
