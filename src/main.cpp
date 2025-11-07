#include <iostream>
#include <vector>
#include <iomanip>
#include "../lib/include/Calculator.hpp"
#include "../lib/include/CalculationPolicies.hpp"

/* 
To build project manually:
g++ -std=c++20 -I lib/include src/main.cpp -o main

To run with Bazel:
bazel run //src:Main
*/

int main() {
    std::cout << "========================================\n";
    std::cout << "Policy-Based Design Calculator - C++20\n";
    std::cout << "========================================\n\n";
    
    // Set output precision for nice formatting
    std::cout << std::fixed << std::setprecision(2);
    
    // ========================================================================
    // Present Value Calculation
    // ========================================================================
    std::cout << "1. PRESENT VALUE CALCULATION\n";
    std::cout << "----------------------------\n";
    
    Calculator<PresentValuePolicy> pv_calculator;
    
    // Example: Bond with annual coupon payments
    double discount_rate = 0.08;  // 8% discount rate
    std::vector<double> cash_flows = {100.0, 100.0, 100.0, 1100.0};  // 3 coupons + principal
    
    std::cout << "Scenario: Bond with $100 annual coupons and $1000 principal\n";
    std::cout << "Discount Rate: " << (discount_rate * 100) << "%\n";
    std::cout << "Cash Flows: ";
    for (size_t i = 0; i < cash_flows.size(); ++i) {
        std::cout << "$" << cash_flows[i];
        if (i < cash_flows.size() - 1) std::cout << ", ";
    }
    std::cout << "\n\n";
    
    double present_value = pv_calculator.calculate(discount_rate, cash_flows);
    
    std::cout << "\n** Result: Present Value = $" << present_value << " **\n";
    std::cout << "\n========================================\n\n";
    
    // ========================================================================
    // Future Value Calculation
    // ========================================================================
    std::cout << "2. FUTURE VALUE CALCULATION\n";
    std::cout << "---------------------------\n";
    
    Calculator<FutureValuePolicy> fv_calculator;
    
    double principal = 10000.0;      // $10,000 initial investment
    double interest_rate = 0.06;     // 6% annual interest
    int periods = 10;                // 10 years
    
    std::cout << "Scenario: Investment growth over time\n";
    std::cout << "Principal: $" << principal << "\n";
    std::cout << "Interest Rate: " << (interest_rate * 100) << "% per year\n";
    std::cout << "Time Period: " << periods << " years\n\n";
    
    double future_value = fv_calculator.calculate(principal, interest_rate, periods);
    
    std::cout << "\n** Result: Future Value = $" << future_value << " **\n";
    std::cout << "** Gain: $" << (future_value - principal) << " **\n";
    std::cout << "\n========================================\n\n";
    
    // ========================================================================
    // Interest Rate Conversion
    // ========================================================================
    std::cout << "3. INTEREST RATE CONVERSION\n";
    std::cout << "---------------------------\n";
    
    Calculator<InterestRateConversionPolicy> ir_calculator;
    
    double nominal_rate = 0.12;           // 12% nominal annual rate
    int compounding_periods = 12;         // Monthly compounding
    
    std::cout << "Scenario: Convert nominal to effective annual rate\n";
    std::cout << "Nominal Rate: " << (nominal_rate * 100) << "% per year\n";
    std::cout << "Compounding: " << compounding_periods << " times per year (monthly)\n\n";
    
    double effective_rate = ir_calculator.calculate(nominal_rate, compounding_periods);
    
    std::cout << "\n** Result: Effective Annual Rate = " << (effective_rate * 100) << "% **\n";
    std::cout << "** Difference: " << ((effective_rate - nominal_rate) * 100) << " percentage points **\n";
    std::cout << "\n========================================\n\n";
    
    // ========================================================================
    // Multiple Scenarios Comparison
    // ========================================================================
    std::cout << "4. COMPARISON: Different Compounding Frequencies\n";
    std::cout << "------------------------------------------------\n";
    
    double base_nominal = 0.10;  // 10% nominal
    std::vector<std::pair<std::string, int>> frequencies = {
        {"Annual", 1},
        {"Semi-Annual", 2},
        {"Quarterly", 4},
        {"Monthly", 12},
        {"Daily", 365}
    };
    
    std::cout << "Nominal Rate: " << (base_nominal * 100) << "%\n\n";
    std::cout << std::left << std::setw(15) << "Frequency" 
              << std::setw(12) << "Periods/Yr"
              << std::setw(15) << "Effective Rate\n";
    std::cout << std::string(42, '-') << "\n";
    
    for (const auto& freq : frequencies) {
        double eff = ir_calculator.calculate(base_nominal, freq.second);
        std::cout << std::left << std::setw(15) << freq.first
                  << std::setw(12) << freq.second
                  << std::setw(15) << (eff * 100) << "%\n";
    }
    
    std::cout << "\n========================================\n";
    std::cout << "All calculations completed successfully!\n";
    std::cout << "========================================\n";
    
    return 0;
}
