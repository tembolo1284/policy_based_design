#include <iostream>
#include <stdio.h>
#include "../lib/include/Calculator.hpp"
#include "../lib/include/CalculationPolicies.hpp"

/* to build project manually one can run
g++ -I lib/include src/main.cpp lib/src/*.cpp -o main

To run the bazel command:

bazel run src:Main

*/

int main() {
    // Instantiate the Calculator with PresentValuePolicy
    Calculator<PresentValuePolicy> presentValueCalculator;
    double presentValue = presentValueCalculator.calculate();

    // Instantiate the Calculator with FutureValuePolicy
    Calculator<FutureValuePolicy> futureValueCalculator;
    double futureValue = futureValueCalculator.calculate();

    // Instantiate the Calculator with InterestRateConversionPolicy
    Calculator<InterestRateConversionPolicy> interestRateCalculator;
    double convertedInterestRate = interestRateCalculator.calculate();

    // Use the calculated values as needed
    // ...
    return 0;
}
