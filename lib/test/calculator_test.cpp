#include <gtest/gtest.h>
#include "../include/Calculator.hpp"
#include "../include/CalculationPolicies.hpp"


TEST(PresentValuePolicyTest, Calculate) {
    double presentValue = PresentValuePolicy::calculate();
    // Add your assertions here to check if the calculated present value is as expected
    ASSERT_EQ(presentValue, 1.1);
}

TEST(FutureValuePolicyTest, Calculate) {
    double futureValue = FutureValuePolicy::calculate();
    // Add your assertions here to check if the calculated future value is as expected
    ASSERT_EQ(futureValue, 2.2);
}

TEST(InterestRateConversionPolicyTest, Calculate) {
    double convertedInterestRate = InterestRateConversionPolicy::calculate();
    // Add your assertions here to check if the calculated converted interest rate is as expected
    ASSERT_EQ(convertedInterestRate, 3.3);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}