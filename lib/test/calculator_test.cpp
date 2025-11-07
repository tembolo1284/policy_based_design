#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "../include/Calculator.hpp"
#include "../include/CalculationPolicies.hpp"

// ===========================================================================
// Present Value Policy Tests
// ===========================================================================

TEST(PresentValuePolicyTest, BasicCalculation) {
    Calculator<PresentValuePolicy> calc;
    
    // Simple case: $100 one year from now at 10% discount rate
    // PV = 100 / (1.10) = 90.909...
    std::vector<double> cash_flows = {100.0};
    double pv = calc.calculate(0.10, cash_flows);
    std::cout << "pv = " << pv << "\n";    
    ASSERT_NEAR(pv, 90.909, 0.01);
}

TEST(PresentValuePolicyTest, MultipleCashFlows) {
    Calculator<PresentValuePolicy> calc;
    
    // Three years of $100 at 5% discount
    // PV = 100/1.05 + 100/1.05^2 + 100/1.05^3
    // PV ≈ 95.24 + 90.70 + 86.38 = 272.32
    std::vector<double> cash_flows = {100.0, 100.0, 100.0};
    double pv = calc.calculate(0.05, cash_flows);
    
    ASSERT_NEAR(pv, 272.32, 0.01);
}

TEST(PresentValuePolicyTest, BondValuation) {
    Calculator<PresentValuePolicy> calc;
    
    // Bond: 3 years, $50 annual coupon, $1000 face value, 6% discount
    std::vector<double> cash_flows = {50.0, 50.0, 1050.0};
    double pv = calc.calculate(0.06, cash_flows);
    std::cout << "pv = " << pv << "\n";
    ASSERT_NEAR(pv, 973.27, 1.0);
}

TEST(PresentValuePolicyTest, EmptyCashFlows) {
    Calculator<PresentValuePolicy> calc;
    
    std::vector<double> empty_flows;
    
    ASSERT_THROW(calc.calculate(0.05, empty_flows), std::invalid_argument);
}

TEST(PresentValuePolicyTest, InvalidDiscountRate) {
    Calculator<PresentValuePolicy> calc;
    
    std::vector<double> cash_flows = {100.0};
    
    // Discount rate of -1 or less is invalid
    ASSERT_THROW(calc.calculate(-1.5, cash_flows), std::invalid_argument);
}

// ===========================================================================
// Future Value Policy Tests
// ===========================================================================

TEST(FutureValuePolicyTest, BasicCalculation) {
    Calculator<FutureValuePolicy> calc;
    
    // $1000 at 5% for 10 years
    // FV = 1000 * (1.05)^10 = 1628.89
    double fv = calc.calculate(1000.0, 0.05, 10);
    
    ASSERT_NEAR(fv, 1628.89, 0.01);
}

TEST(FutureValuePolicyTest, DoubleYourMoney) {
    Calculator<FutureValuePolicy> calc;
    
    // Rule of 72: ~7.2 years to double at 10%
    // FV = 1000 * (1.10)^7 ≈ 1948.72
    double fv = calc.calculate(1000.0, 0.10, 7);
    
    ASSERT_GT(fv, 1900.0);  // Should be close to double
    ASSERT_LT(fv, 2000.0);
}

TEST(FutureValuePolicyTest, ZeroPeriods) {
    Calculator<FutureValuePolicy> calc;
    
    // Zero periods means no growth
    double fv = calc.calculate(1000.0, 0.05, 0);
    
    ASSERT_DOUBLE_EQ(fv, 1000.0);
}

TEST(FutureValuePolicyTest, NegativePrincipal) {
    Calculator<FutureValuePolicy> calc;
    
    ASSERT_THROW(calc.calculate(-1000.0, 0.05, 10), std::invalid_argument);
}

TEST(FutureValuePolicyTest, NegativePeriods) {
    Calculator<FutureValuePolicy> calc;
    
    ASSERT_THROW(calc.calculate(1000.0, 0.05, -5), std::invalid_argument);
}

TEST(FutureValuePolicyTest, InvalidInterestRate) {
    Calculator<FutureValuePolicy> calc;
    
    ASSERT_THROW(calc.calculate(1000.0, -1.5, 10), std::invalid_argument);
}

// ===========================================================================
// Interest Rate Conversion Policy Tests
// ===========================================================================

TEST(InterestRateConversionPolicyTest, AnnualCompounding) {
    Calculator<InterestRateConversionPolicy> calc;
    
    // Annual compounding: effective = nominal
    double effective = calc.calculate(0.10, 1);
    
    ASSERT_DOUBLE_EQ(effective, 0.10);
}

TEST(InterestRateConversionPolicyTest, SemiAnnualCompounding) {
    Calculator<InterestRateConversionPolicy> calc;
    
    // 10% nominal, semi-annual compounding
    // EAR = (1 + 0.10/2)^2 - 1 = 1.05^2 - 1 = 0.1025
    double effective = calc.calculate(0.10, 2);
    
    ASSERT_NEAR(effective, 0.1025, 0.0001);
}

TEST(InterestRateConversionPolicyTest, MonthlyCompounding) {
    Calculator<InterestRateConversionPolicy> calc;
    
    // 12% nominal, monthly compounding
    // EAR = (1 + 0.12/12)^12 - 1 = 1.01^12 - 1 ≈ 0.1268
    double effective = calc.calculate(0.12, 12);
    
    ASSERT_NEAR(effective, 0.1268, 0.0001);
}

TEST(InterestRateConversionPolicyTest, DailyCompounding) {
    Calculator<InterestRateConversionPolicy> calc;
    
    // 6% nominal, daily compounding (365 days)
    // EAR = (1 + 0.06/365)^365 - 1 ≈ 0.0618
    double effective = calc.calculate(0.06, 365);
    
    ASSERT_NEAR(effective, 0.0618, 0.0001);
}

TEST(InterestRateConversionPolicyTest, ContinuousCompounding) {
    Calculator<InterestRateConversionPolicy> calc;
    
    // Very high compounding frequency approximates continuous compounding
    // For 10% nominal with 10000 periods
    double effective = calc.calculate(0.10, 10000);
    
    // Continuous: e^0.10 - 1 ≈ 0.10517
    // With 10000 periods should be very close
    ASSERT_NEAR(effective, 0.10517, 0.0001);
}

TEST(InterestRateConversionPolicyTest, ZeroCompoundingPeriods) {
    Calculator<InterestRateConversionPolicy> calc;
    
    ASSERT_THROW(calc.calculate(0.10, 0), std::invalid_argument);
}

TEST(InterestRateConversionPolicyTest, NegativeCompoundingPeriods) {
    Calculator<InterestRateConversionPolicy> calc;
    
    ASSERT_THROW(calc.calculate(0.10, -12), std::invalid_argument);
}

TEST(InterestRateConversionPolicyTest, InvalidNominalRate) {
    Calculator<InterestRateConversionPolicy> calc;
    
    ASSERT_THROW(calc.calculate(-1.5, 12), std::invalid_argument);
}

// ===========================================================================
// Integration Tests - Multiple Policies
// ===========================================================================

TEST(IntegrationTest, PresentValueFutureValueRoundTrip) {
    Calculator<PresentValuePolicy> pv_calc;
    Calculator<FutureValuePolicy> fv_calc;
    
    // Start with $1000, grow it at 8% for 5 years
    double future = fv_calc.calculate(1000.0, 0.08, 5);
    
    // Now discount that future value back to present
    std::vector<double> cash_flows(4, 0.0);
    cash_flows.push_back(future);
    
    double present = pv_calc.calculate(0.08, cash_flows);
    std::cout << "present = " << present << "\n"; 
    // Should get back approximately $1000
    ASSERT_NEAR(present, 1000.0, 1.0);
}

TEST(IntegrationTest, EffectiveRateImpact) {
    Calculator<InterestRateConversionPolicy> ir_calc;
    Calculator<FutureValuePolicy> fv_calc;
    
    double principal = 10000.0;
    double nominal = 0.12;
    int years = 5;
    
    // Calculate with annual compounding (nominal = effective)
    double fv_annual = fv_calc.calculate(principal, nominal, years);
    
    // Calculate effective rate with monthly compounding
    double effective = ir_calc.calculate(nominal, 12);
    
    // Calculate FV with effective rate
    double fv_monthly = fv_calc.calculate(principal, effective, years);
    
    // Monthly compounding should yield more
    ASSERT_GT(fv_monthly, fv_annual);
}

// ===========================================================================
// Main Test Runner
// ===========================================================================

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
