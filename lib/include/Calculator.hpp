#ifndef Calculator_HPP
#define Calculator_HPP

#include <iostream>
#include <string>
#include <vector>

// ===========================================================================
// Calculator Template Class
// ===========================================================================
// Policy-based calculator that delegates calculations to the policy class.
// The policy determines the calculation logic and signature.
//
// Template Parameter:
//   CalculationPolicy - A policy class that provides a static calculate() method
//
// Example Usage:
//   Calculator<PresentValuePolicy> pv_calc;
//   double result = pv_calc.calculate(0.05, {100.0, 200.0, 300.0});
// ===========================================================================

template <typename CalculationPolicy>
class Calculator {
public:
    // ========================================================================
    // Present Value Calculation
    // For Calculator<PresentValuePolicy>
    // ========================================================================
    double calculate(double discount_rate, const std::vector<double>& cash_flows) {
        return CalculationPolicy::calculate(discount_rate, cash_flows);
    }
    
    // ========================================================================
    // Future Value Calculation
    // For Calculator<FutureValuePolicy>
    // ========================================================================
    double calculate(double principal, double interest_rate, int periods) {
        return CalculationPolicy::calculate(principal, interest_rate, periods);
    }
    
    // ========================================================================
    // Interest Rate Conversion
    // For Calculator<InterestRateConversionPolicy>
    // ========================================================================
    double calculate(double nominal_rate, int compounding_periods) {
        return CalculationPolicy::calculate(nominal_rate, compounding_periods);
    }
};

#endif
