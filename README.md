# Policy-Based Design for Financial Mathematics

A C++ library demonstrating Policy-Based Design patterns for financial calculations, with Python bindings via pybind11.

## Overview

This project showcases the implementation of Policy-Based Design in C++ for financial mathematics. By employing policy classes, you can easily modify the behavior of financial calculators without altering their core implementation. This separation of concerns allows for better code reuse, maintainability, and adaptability to different financial scenarios.

## Features

- **Policy-Based Design**: Flexible, template-based architecture
- **C++20**: Modern C++ with strict warning flags
- **Python Bindings**: Use your C++ library from Python via pybind11
- **Bazel Build System**: Fast, reliable builds with multiple configurations
- **Comprehensive Testing**: Google Test integration
- **Multiple Compilers**: Support for GCC and Clang

## Project Structure
```
policy_based_design/
├── WORKSPACE              # Bazel workspace with dependencies
├── .bazelrc              # Build configuration (C++20, warnings, compilers)
├── build.sh              # Convenient build script
├── lib/                  # C++ library
│   ├── BUILD
│   ├── include/
│   │   ├── Calculator.hpp
│   │   └── CalculationPolicies.hpp
│   └── test/
│       └── calculator_test.cpp
├── src/                  # C++ main application
│   ├── BUILD
│   └── main.cpp
└── python/               # Python bindings
    ├── BUILD
    ├── bindings.cpp
    ├── __init__.py
    └── example.py
```

## Quick Start

### Prerequisites

- **Bazel** (https://bazel.build/install)
- **GCC** or **Clang** compiler
- **Python 3.11+** (for Python bindings)

### Build Everything
```bash
# Clean build with tests
./build.sh --clean --all --release

# Quick debug build
./build.sh --build --test
```

### Run Examples
```bash
# Run C++ example
./build.sh --cpp

# Run Python example
./build.sh --python

# Or directly with Bazel
bazel run //src:Main
bazel run //python:example
```

## Build Script Usage

The `build.sh` script provides a convenient interface to Bazel:
```bash
./build.sh [OPTIONS]

Actions:
  --clean              Clean all build artifacts
  --build              Build all targets
  --test               Run all tests
  --all                Build and test everything
  --python             Build and run Python example
  --cpp                Build and run C++ main

Compiler Selection:
  --compiler=gcc       Use GCC compiler (default)
  --compiler=clang     Use Clang compiler

Build Mode:
  --debug              Debug build with symbols (default)
  --release            Optimized release build

Other:
  --verbose            Show detailed Bazel output
  --help               Show help message
```

### Examples
```bash
# Full release build with GCC
./build.sh --clean --all --compiler=gcc --release

# Debug build and test with Clang
./build.sh --build --test --compiler=clang --debug

# Run both C++ and Python examples
./build.sh --cpp --python --release

# Just run tests
./build.sh --test
```

## C++ Usage

### Basic Example
```cpp
#include "lib/include/Calculator.hpp"
#include "lib/include/CalculationPolicies.hpp"

int main() {
    // Instantiate calculator with specific policy
    Calculator<PresentValuePolicy> pvCalculator;
    double presentValue = pvCalculator.calculate();
    
    Calculator<FutureValuePolicy> fvCalculator;
    double futureValue = fvCalculator.calculate();
    
    Calculator<InterestRateConversionPolicy> irCalculator;
    double convertedRate = irCalculator.calculate();
    
    return 0;
}
```

### Available Policies

- **PresentValuePolicy**: Calculate present value
- **FutureValuePolicy**: Calculate future value
- **InterestRateConversionPolicy**: Convert interest rates

## Python Usage

### Installation

The Python bindings are built automatically with the C++ library.

### Basic Example
```python
from calculator import (
    PresentValueCalculator,
    FutureValueCalculator,
    InterestRateCalculator,
)

# Create calculators
pv_calc = PresentValueCalculator()
fv_calc = FutureValueCalculator()
ir_calc = InterestRateCalculator()

# Perform calculations
present_value = pv_calc.calculate()
future_value = fv_calc.calculate()
converted_rate = ir_calc.calculate()

print(f"Present Value: {present_value}")
print(f"Future Value: {future_value}")
print(f"Interest Rate: {converted_rate}")
```

### Running Python Example
```bash
# With build script
./build.sh --python --release

# Directly with Bazel
bazel run //python:example
```

## Testing

### Run All Tests
```bash
./build.sh --test
```

### Run Specific Test
```bash
bazel test //lib/test:Calculator_Test
```

### Test with Different Configurations
```bash
# Debug mode with GCC
./build.sh --test --compiler=gcc --debug

# Release mode with Clang
./build.sh --test --compiler=clang --release
```

## Direct Bazel Commands

If you prefer using Bazel directly:
```bash
# Build everything
bazel build //...

# Run tests
bazel test //...

# Build with specific configuration
bazel build //... --config=gcc --config=release

# Run C++ main
bazel run //src:Main

# Run Python example
bazel run //python:example

# Clean
bazel clean --expunge
```

## Key Concepts

### Policy-Based Design

Policy classes are independent classes or templates that define specific behaviors or algorithms. These policies can be combined and provided as template arguments to the main class, allowing for various combinations and customization.

### Template-Based Calculator

The `Calculator` class is a template that accepts a policy class:
```cpp
template <typename CalculationPolicy>
class Calculator {
public:
    double calculate() {
        return CalculationPolicy::calculate();
    }
};
```

This design allows you to:
- ✅ Add new policies without modifying existing code
- ✅ Combine different policies at compile-time
- ✅ Maintain type safety and zero runtime overhead
- ✅ Create highly customizable and reusable components

## Development

### Adding New Policies

1. Add policy class to `lib/include/CalculationPolicies.hpp`:
```cpp
class NewPolicy {
public:
    static double calculate() {
        // Your implementation
        return 42.0;
    }
};
```

2. Add Python binding to `python/bindings.cpp`:
```cpp
py::class_<Calculator<NewPolicy>>(m, "NewCalculator")
    .def(py::init<>())
    .def("calculate", &Calculator<NewPolicy>::calculate);
```

3. Export in `python/__init__.py`:
```python
from .calculator_py import NewCalculator

__all__ = ['NewCalculator', ...]
```

### Build Configuration

The `.bazelrc` file contains build configurations:

- **C++20 standard** with strict warnings (`-Wall -Wextra -Werror`)
- **Compiler configs**: GCC (default) and Clang
- **Build modes**: Debug (default) and Release
- **Test output**: Detailed error reporting

### Compiler Flags

Strict warning flags enabled:
- `-Wall -Wextra -Werror`: Treat all warnings as errors
- `-Wpedantic`: Strict ISO C++ compliance
- `-Wshadow`: Warn about variable shadowing
- `-Wconversion`: Warn about implicit conversions
- `-Wold-style-cast`: Prefer C++ style casts
- And many more...

## Dependencies

- **Bazel**: Build system
- **Google Test**: C++ testing framework
- **pybind11**: C++/Python bindings
- **Python 3.11+**: For Python bindings
