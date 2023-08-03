# policy_based_design

Policy-Based Design in C++ for Financial Mathematics

Policy-Based Design is a powerful software development technique in C++ that allows you to create highly customizable and flexible classes through the use of policy classes. In the domain of financial mathematics, Policy-Based Design can be effectively employed to create generic and adaptable financial calculators for various financial instruments and calculations.

## Overview

This project showcases the implementation of Policy-Based Design in C++ for financial mathematics. By employing policy classes, you can easily modify the behavior of financial calculators without altering their core implementation. This separation of concerns allows for better code reuse, maintainability, and adaptability to different financial scenarios.

## Key Concepts

- **Policy Classes**: Policy classes are independent classes or templates that define specific behaviors or algorithms. These policies can be combined and provided as template arguments to the main class, allowing for various combinations and customization.

- **Calculator Class**: The main class in this project is the financial calculator, which is designed using Policy-Based Design. The calculator class provides a common interface for financial calculations and delegates specific calculations to the attached policy classes.

## Project Structure

The project consists of the following components:

- `include/Calculator.hpp`: Header file containing the implementation of the financial calculator class using Policy-Based Design.
- `src/calculator.cpp`: Source file containing the implementation of the methods in `calculator.hpp`.
- `include/CalculationPolicies.hpp`: Header file containing the various policy classes for financial calculations. Can be generalized to anything beyond just calculations. Could be curve building, interpolation schemes, optimization schemes, anything applicable.
- `tests/calculator_test.cpp`: Test file using Google Test to verify the functionality of the financial calculator with different policy combinations.
- `main.cpp`: The main program file where you can use the financial calculator with different policy combinations for real-world financial calculations.

## Building and Running

Follow the steps below to build and run the project:

1. Build the project by typing: `bazel build src:Main`
2. Run the project by typing: `bazel run src:Main`
3. You can build the project manually with g++ by typing: `g++ -I include src/main.cpp -o main`

## Usage

To use the Policy-Based Design for financial calculations in your own project:

1. Include the `Calculator.hpp` header file in your source files where you want to use the financial calculator.
2. Create and customize your own policy classes or use the existing `CalculationPolicies.hpp` to provide specific financial calculation algorithms.
3. Instantiate the financial calculator class with desired policy combinations.
4. Use the financial calculator to perform various financial calculations based on the attached policies.

Refer to the examples in `main.cpp` and `calculator_test.cpp` to see how to utilize the Policy-Based Design for financial mathematics.

## Testing

The project includes unit tests for verifying the correctness of the financial calculator's behavior with different policy combinations. To run the tests, simply type: `bazel test lib/test:Calculator_Test`
