#ifndef CALCULATIONPOLICIES_HPP
#define CALCULATIONPOLICIES_HPP

#include <vector>
#include <cmath>
#include <stdexcept>
#include <cstddef>

// ===========================================================================
// PresentValuePolicy
// PV = Σ_{i=0..n-1} CF_i / (1 + r)^(i+1)
//   • All cash flows are future-dated: the first element occurs at t = 1
//   • discount_rate is decimal (e.g., 0.05 for 5%)
// ===========================================================================
struct PresentValuePolicy {
    static double calculate(double discount_rate, const std::vector<double>& cash_flows) {
        if (discount_rate <= -1.0) {
            throw std::invalid_argument("discount_rate must be > -1");
        }
        if (cash_flows.empty()) {
            throw std::invalid_argument("cash_flows must not be empty");
        }

        const double base = 1.0 + discount_rate;
        double pv = 0.0;
        for (std::size_t i = 0; i < cash_flows.size(); ++i) {
            const double t = static_cast<double>(i) + 1.0; // first CF discounted once
            pv += cash_flows[i] / std::pow(base, t);
        }
        return pv;
    }
};

// ===========================================================================
// FutureValuePolicy
// FV = PV * (1 + r)^n
//   • interest_rate is decimal (e.g., 0.05 for 5%)
//   • periods is a nonnegative integer
// ===========================================================================
struct FutureValuePolicy {
    static double calculate(double principal, double interest_rate, int periods) {
        if (principal < 0.0) {
            throw std::invalid_argument("principal must be >= 0");
        }
        if (interest_rate <= -1.0) {
            throw std::invalid_argument("interest_rate must be > -1");
        }
        if (periods < 0) {
            throw std::invalid_argument("periods must be >= 0");
        }

        return principal * std::pow(1.0 + interest_rate, static_cast<double>(periods));
    }
};

// ===========================================================================
// InterestRateConversionPolicy
// Effective Annual Rate (EAR) from nominal r with n compounding periods/year:
// EAR = (1 + r/n)^n - 1
//   • For n = 1, return r exactly (avoids tiny FP diffs in strict tests)
// ===========================================================================
struct InterestRateConversionPolicy {
    static double calculate(double nominal_rate, int compounding_periods) {
        if (nominal_rate <= -1.0) {
            throw std::invalid_argument("nominal_rate must be > -1");
        }
        if (compounding_periods <= 0) {
            throw std::invalid_argument("compounding_periods must be > 0");
        }

        if (compounding_periods == 1) {
            return nominal_rate;
        }
        const double n = static_cast<double>(compounding_periods);
        return std::pow(1.0 + nominal_rate / n, n) - 1.0;
    }
};

#endif // CALCULATIONPOLICIES_HPP

