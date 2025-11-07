#include <pybind11/pybind11.h>
#include <pybind11/stl.h>  // CRITICAL: For automatic std::vector conversion!
#include "lib/include/Calculator.hpp"
#include "lib/include/CalculationPolicies.hpp"

namespace py = pybind11;

PYBIND11_MODULE(calculator_py, m) {
    m.doc() = "Policy-Based Design Calculator for Financial Mathematics\n\n"
              "This module provides financial calculators with real mathematical logic:\n"
              "  - Present Value: Calculate PV of future cash flows\n"
              "  - Future Value: Calculate FV of a principal amount\n"
              "  - Interest Rate Conversion: Convert nominal to effective annual rate";
    
    // ===========================================================================
    // Calculator<PresentValuePolicy>
    // ===========================================================================
    py::class_<Calculator<PresentValuePolicy>>(m, "PresentValueCalculator",
        "Calculator for Present Value of future cash flows\n\n"
        "Formula: PV = Σ(CF_t / (1 + r)^t) for t = 1 to n\n\n"
        "Example:\n"
        "    >>> calc = PresentValueCalculator()\n"
        "    >>> pv = calc.calculate(0.05, [100.0, 200.0, 300.0])\n"
        "    >>> print(f'Present Value: {pv:.2f}')")
        
        .def(py::init<>(), 
             "Create a Present Value calculator")
        
        .def("calculate", 
             &Calculator<PresentValuePolicy>::calculate,
             py::arg("discount_rate"), 
             py::arg("cash_flows"),
             "Calculate present value of future cash flows\n\n"
             "Args:\n"
             "    discount_rate (float): The discount rate (e.g., 0.05 for 5%)\n"
             "    cash_flows (list[float]): List of future cash flows\n\n"
             "Returns:\n"
             "    float: The present value of all cash flows\n\n"
             "Raises:\n"
             "    ValueError: If cash_flows is empty or discount_rate <= -1\n\n"
             "Example:\n"
             "    >>> calc.calculate(0.10, [100, 100, 100])\n"
             "    248.69");
    
    // ===========================================================================
    // Calculator<FutureValuePolicy>
    // ===========================================================================
    py::class_<Calculator<FutureValuePolicy>>(m, "FutureValueCalculator",
        "Calculator for Future Value of a principal amount\n\n"
        "Formula: FV = PV * (1 + r)^n\n\n"
        "Example:\n"
        "    >>> calc = FutureValueCalculator()\n"
        "    >>> fv = calc.calculate(1000.0, 0.05, 10)\n"
        "    >>> print(f'Future Value: {fv:.2f}')")
        
        .def(py::init<>(), 
             "Create a Future Value calculator")
        
        .def("calculate", 
             &Calculator<FutureValuePolicy>::calculate,
             py::arg("principal"), 
             py::arg("interest_rate"),
             py::arg("periods"),
             "Calculate future value of a principal amount\n\n"
             "Args:\n"
             "    principal (float): Initial investment amount\n"
             "    interest_rate (float): Interest rate per period (e.g., 0.05 for 5%)\n"
             "    periods (int): Number of compounding periods\n\n"
             "Returns:\n"
             "    float: The future value after all periods\n\n"
             "Raises:\n"
             "    ValueError: If principal < 0, periods < 0, or interest_rate <= -1\n\n"
             "Example:\n"
             "    >>> calc.calculate(1000, 0.08, 5)\n"
             "    1469.33");
    
    // ===========================================================================
    // Calculator<InterestRateConversionPolicy>
    // ===========================================================================
    py::class_<Calculator<InterestRateConversionPolicy>>(m, "InterestRateCalculator",
        "Calculator for Interest Rate Conversion (Nominal to Effective)\n\n"
        "Formula: EAR = (1 + r/n)^n - 1\n\n"
        "Example:\n"
        "    >>> calc = InterestRateCalculator()\n"
        "    >>> ear = calc.calculate(0.12, 12)  # 12% nominal, monthly compounding\n"
        "    >>> print(f'Effective Annual Rate: {ear:.4f}')")
        
        .def(py::init<>(), 
             "Create an Interest Rate Conversion calculator")
        
        .def("calculate", 
             &Calculator<InterestRateConversionPolicy>::calculate,
             py::arg("nominal_rate"),
             py::arg("compounding_periods"),
             "Convert nominal interest rate to effective annual rate\n\n"
             "Args:\n"
             "    nominal_rate (float): Nominal annual interest rate (e.g., 0.12 for 12%)\n"
             "    compounding_periods (int): Number of compounding periods per year\n"
             "                               (e.g., 12 for monthly, 4 for quarterly)\n\n"
             "Returns:\n"
             "    float: Effective annual rate (EAR)\n\n"
             "Raises:\n"
             "    ValueError: If compounding_periods <= 0 or nominal_rate <= -1\n\n"
             "Example:\n"
             "    >>> calc.calculate(0.06, 12)  # 6% nominal, monthly\n"
             "    0.0617");
}
