# Cheapest to Deliver (CTD) Basket Calculator

A basic C++ terminal-based calculator for analyzing a basket of deliverable U.S. Treasury securities against a Treasury futures contract.

The program calculates coupon payments, accrued interest, dirty prices, projected accrued interest, repo financing costs, converted futures prices, invoice prices, gross basis, and net basis.

It then compares the net basis of each security to identify the **Cheapest to Deliver (CTD)** candidate.

---

## 1. General Purpose

The purpose of this calculator is to simplify the comparison of deliverable Treasury securities within a futures contract.

By combining Treasury pricing mechanics with basic repo financing calculations, the program provides a structured view of how individual securities compare against the market futures price.

The calculator is designed for:
- Treasury futures basis analysis
- CTD basket comparisons
- Accrued interest calculations
- Repo financing cost estimation
- Gross basis and net basis analysis
- Basic fixed-income research and education

---

## 2. Inputs

The program begins by requesting the market futures price, delivery timeframe, and number of securities in the delivery basket.

### Market Futures Inputs

| Input | Description |
|---|---|
| Market Futures Price | Current market price of the futures contract |
| Days to Delivery | Number of days until delivery |
| Basket Size | Number of securities to compare |

### Individual Treasury Inputs

Each security requires the following information:

| Input | Description |
|---|---|
| CUSIP | Security identification |
| Repo | Annualized repo financing rate |
| CF | Futures conversion factor |
| Par | Treasury par value |
| Clean Price | Quoted Treasury price |
| Coupon Rate | Annual coupon rate |
| Coupon Frequency | Annual coupon payment frequency |
| Days Since Last Coupon | Days elapsed since the previous coupon |
| Days in Coupon Period | Total days in the current coupon period |

**Input conventions:**
- Repo rates: decimal format (0.04 = 4%)
- Coupon rates: decimal format (0.045 = 4.5%)
- Conversion factors: decimal format
- Par and clean prices: 100-notional price convention
- Coupon frequency: numerical value (2 = semiannual)

---

## 3. Calculations & Mathematics

### General Treasury Calculations

**Coupon Payment**

Calculates the periodic coupon payment.

`Coupon Payment = (Par × Coupon Rate) / Frequency`

**Accrued Interest**

Calculates accrued coupon interest since the previous coupon payment.

`Accrued Interest = (Days Since Last Coupon / Days in Coupon Period) × Coupon Payment`

**Dirty Price**

Adds accrued interest to the clean Treasury price.

`Dirty Price = Clean Price + Accrued Interest`

**Projected Accrued Interest**

Estimates accrued interest at delivery.

`Projected AI = Current AI + (Days to Delivery / Days in Coupon Period) × Coupon Payment`

**Repo Financing Cost**

Estimates the financing cost of holding the Treasury until delivery.

`Repo Cost = Dirty Price × Repo Rate × (Days to Delivery / 360)`

---

### Futures & Basis Calculations

**Converted Futures Price**

Applies the Treasury conversion factor to the market futures price.

`Converted Futures = Market Futures Price × Conversion Factor`

**Invoice Price**

Calculates the futures delivery invoice using the converted futures price and projected accrued interest.

`Invoice Price = Converted Futures + Projected AI`

**Gross Basis**

Measures the difference between the Treasury dirty price and converted futures price.

`Gross Basis = Dirty Price − Converted Futures`

**Net Basis**

Measures the difference between the Treasury dirty price and the projected futures invoice price.

`Net Basis = Dirty Price − Invoice Price`

---

## 4. Outputs

The program generates three tables.

### Table 1 — Inputs

Displays the original security inputs:

- CUSIP
- Repo rate
- Conversion factor
- Days to delivery
- Par value
- Clean price
- Coupon rate
- Coupon frequency
- Days since last coupon
- Coupon period length

### Table 2 — Financing

Displays the calculated financing components:

- Coupon payment
- Accrued interest
- Dirty price
- Projected accrued interest
- Repo financing cost

### Table 3 — Futures & Basis

Displays the futures-related calculations:

- Market futures price
- Converted futures price
- Invoice price
- Gross basis
- Net basis

### Final Output — Cheapest to Deliver

The program compares the net basis of every security in the basket.

The security with the lowest calculated net basis is selected as the CTD candidate.

The terminal displays:

- CTD CUSIP
- Corresponding net basis

---

## 5. Technical Information

| Component | Implementation |
|---|---|
| Language | C++ |
| Standard Libraries | iostream, vector, string, iomanip |
| Data Structure | Struct and vector |
| Calculations | User-defined functions |
| Output | Formatted terminal tables |
| Security Comparison | Iterative minimum-value search |

The program uses a `ctdbasket` structure to store individual Treasury security inputs and calculated values.

A vector stores the securities, allowing the program to compare multiple deliverable bonds within a single futures basket.

---

## 6. Model Limitations

This is a simplified CTD comparison model.

The calculations do not currently incorporate:

- Coupon payment date adjustments and holiday calendars
- Actual Treasury day-count conventions for every security
- Repo specialness and term-specific financing curves
- Coupon cash-flow reinvestment
- Delivery timing and delivery option valuation
- Wildcard and end-of-month options
- Full carry-adjusted net basis or implied repo rate optimization

Repo financing is estimated using a simple 360-day convention.

The projected accrued interest calculation assumes a single coupon period and does not independently adjust for a coupon payment occurring before delivery.

**The calculated lowest net basis should therefore be interpreted as a simplified model output, not a complete market-standard CTD determination.**

---

## 7. Project Information

**Author:** Robert Nikolas Daniel  
**GitHub:** RobertNikolasDaniel

Built as an independent fixed-income research project focused on Treasury futures, financing mechanics, and deliverable basket analysis.

**NO AI USED — Independently written and debugged C++ project.**
