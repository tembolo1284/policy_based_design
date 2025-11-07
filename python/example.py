#!/usr/bin/env python3
"""Example usage of the Policy-Based Design Calculator with real financial math
"""

from python import (
    PresentValueCalculator,
    FutureValueCalculator,
    InterestRateCalculator,
)


def print_header(title):
    """Print a formatted section header."""
    print("\n" + "=" * 60)
    print(title)
    print("=" * 60)


def print_subheader(title):
    """Print a formatted subsection header."""
    print(f"\n{title}")
    print("-" * len(title))


def example_present_value():
    """Demonstrate Present Value calculation with multiple cash flows."""
    print_header("1. PRESENT VALUE CALCULATION")
    
    calc = PresentValueCalculator()
    
    # Example 1: Bond valuation
    print_subheader("Example 1: Bond with annual coupons")
    discount_rate = 0.08  # 8% discount rate
    cash_flows = [100.0, 100.0, 100.0, 1100.0]  # 3 coupons + principal
    
    print(f"Discount Rate: {discount_rate * 100}%")
    print(f"Cash Flows: ${', $'.join(map(str, cash_flows))}")
    
    pv = calc.calculate(discount_rate, cash_flows)
    print(f"\n✓ Present Value: ${pv:.2f}")
    
    # Example 2: Project evaluation
    print_subheader("\nExample 2: Project cash flow analysis")
    project_rate = 0.10  # 10% required return
    project_flows = [-1000.0, 300.0, 400.0, 500.0, 600.0]  # Initial investment + returns
    
    print(f"Required Return: {project_rate * 100}%")
    print(f"Cash Flows: ${', $'.join(map(str, project_flows))}")
    
    npv = calc.calculate(project_rate, project_flows)
    print(f"\n✓ Net Present Value: ${npv:.2f}")
    if npv > 0:
        print("  → Project is PROFITABLE!")
    else:
        print("  → Project is NOT recommended")


def example_future_value():
    """Demonstrate Future Value calculation for investments."""
    print_header("2. FUTURE VALUE CALCULATION")
    
    calc = FutureValueCalculator()
    
    # Example 1: Retirement savings
    print_subheader("Example 1: Retirement savings")
    principal = 10000.0
    interest_rate = 0.07  # 7% annual return
    periods = 30  # 30 years
    
    print(f"Initial Investment: ${principal:,.2f}")
    print(f"Annual Return: {interest_rate * 100}%")
    print(f"Time Horizon: {periods} years")
    
    fv = calc.calculate(principal, interest_rate, periods)
    gain = fv - principal
    
    print(f"\n✓ Future Value: ${fv:,.2f}")
    print(f"✓ Total Gain: ${gain:,.2f}")
    print(f"✓ Return Multiple: {fv / principal:.2f}x")
    
    # Example 2: Compare different time horizons
    print_subheader("\nExample 2: Impact of time on growth")
    base_amount = 5000.0
    rate = 0.08
    
    print(f"Principal: ${base_amount:,.2f}")
    print(f"Interest Rate: {rate * 100}%\n")
    print(f"{'Years':<10} {'Future Value':<20} {'Multiple':<10}")
    print("-" * 40)
    
    for years in [5, 10, 15, 20, 25, 30]:
        fv = calc.calculate(base_amount, rate, years)
        multiple = fv / base_amount
        print(f"{years:<10} ${fv:<19,.2f} {multiple:.2f}x")


def example_interest_rate_conversion():
    """Demonstrate interest rate conversion from nominal to effective."""
    print_header("3. INTEREST RATE CONVERSION")
    
    calc = InterestRateCalculator()
    
    # Example 1: Credit card APR
    print_subheader("Example 1: Credit card APR")
    nominal = 0.18  # 18% APR
    periods = 12    # Monthly compounding
    
    print(f"Nominal APR: {nominal * 100}%")
    print(f"Compounding: {periods} times per year (monthly)")
    
    effective = calc.calculate(nominal, periods)
    
    print(f"\n✓ Effective Annual Rate: {effective * 100:.4f}%")
    print(f"✓ Additional cost: {(effective - nominal) * 100:.4f} percentage points")
    
    # Example 2: Compare compounding frequencies
    print_subheader("\nExample 2: Compounding frequency comparison")
    base_rate = 0.10  # 10% nominal
    
    frequencies = [
        ("Annual", 1),
        ("Semi-Annual", 2),
        ("Quarterly", 4),
        ("Monthly", 12),
        ("Daily", 365),
    ]
    
    print(f"Nominal Rate: {base_rate * 100}%\n")
    print(f"{'Frequency':<15} {'Periods/Year':<15} {'Effective Rate':<15}")
    print("-" * 45)
    
    for name, freq in frequencies:
        eff = calc.calculate(base_rate, freq)
        print(f"{name:<15} {freq:<15} {eff * 100:.4f}%")


def example_real_world_scenario():
    """Demonstrate a complete real-world scenario using multiple calculators."""
    print_header("4. REAL-WORLD SCENARIO: Mortgage Decision")
    
    print("\nScenario: Choosing between two mortgage offers")
    print("House Price: $500,000")
    print("Down Payment: $100,000")
    print("Loan Amount: $400,000")
    
    # Mortgage 1: Lower rate, more frequent compounding
    print_subheader("\nOffer 1: 3.5% APR, monthly payments, 30 years")
    
    pv_calc = PresentValueCalculator()
    fv_calc = FutureValueCalculator()
    ir_calc = InterestRateCalculator()
    
    nominal_1 = 0.035
    periods_per_year_1 = 12
    years_1 = 30
    
    effective_1 = ir_calc.calculate(nominal_1, periods_per_year_1)
    print(f"Effective Annual Rate: {effective_1 * 100:.4f}%")
    
    # Mortgage 2: Higher rate, quarterly compounding
    print_subheader("\nOffer 2: 3.75% APR, quarterly payments, 30 years")
    
    nominal_2 = 0.0375
    periods_per_year_2 = 4
    years_2 = 30
    
    effective_2 = ir_calc.calculate(nominal_2, periods_per_year_2)
    print(f"Effective Annual Rate: {effective_2 * 100:.4f}%")
    
    # Comparison
    print_subheader("\nRecommendation")
    if effective_1 < effective_2:
        savings = effective_2 - effective_1
        print(f"✓ Choose Offer 1!")
        print(f"  Savings: {savings * 100:.4f} percentage points per year")
    else:
        savings = effective_1 - effective_2
        print(f"✓ Choose Offer 2!")
        print(f"  Savings: {savings * 100:.4f} percentage points per year")


def main():
    """Run all examples."""
    print("=" * 60)
    print("POLICY-BASED DESIGN CALCULATOR - PYTHON EXAMPLES")
    print("Financial Mathematics with Real Parameters & Vectors")
    print("=" * 60)
    
    try:
        example_present_value()
        example_future_value()
        example_interest_rate_conversion()
        example_real_world_scenario()
        
        print_header("ALL EXAMPLES COMPLETED SUCCESSFULLY! ✓")
        
    except Exception as e:
        print(f"\n❌ Error: {e}")
        import traceback
        traceback.print_exc()
        return 1
    
    return 0


if __name__ == "__main__":
    exit(main())
