This is a perfect use case for the "Critique an AI-Generated Output" section of your assignment.  For your assignment, you need to save an AI-generated script as ai_planner.cpp and write a reflection (ai_reflection.txt) discussing what the AI did well, what potential problems exist, and if you would trust it.  Below is a "Total AI" professional-grade C++ implementation for Option 3: Recurring Payments Calculation. It strictly adheres to all the constraints, default overrides, and termination conditions outlined in the rubric.  The AI Solution (ai_planner.cpp)C++/**
 * ai_planner.cpp
 * * Program: Recurring Payments Calculator
 * Description: Calculates the periodic savings required to reach a desired 
 * future value over a specified number of years.
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cctype>
#include <limits>

using namespace std;

// --- Helper Functions ---

/**
 * Converts a given string to lowercase for case-insensitive comparisons.
 */
string to_lowercase(string str) {
    for (size_t i = 0; i < str.length(); ++i) {
        str[i] = tolower(str[i]);
    }
    return str;
}

/**
 * Clears the input buffer to recover from invalid data types (e.g., entering letters for numbers).
 */
void clear_input_buffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// --- Input Functions ---

/**
 * Prompts the user for a monetary value and handles basic stream errors.
 */
double get_monetary_input(const string& prompt) {
    double value;
    cout << prompt;
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a numerical value.\n" << prompt;
        clear_input_buffer();
    }
    return value;
}

/**
 * Prompts for the annual return rate, applying the 5% default if negative.
 */
double get_annual_rate() {
    double rate;
    cout << "Enter expected annual rate of return (as a percentage, e.g., 5 for 5%): ";
    while (!(cin >> rate)) {
        cout << "Invalid input. Please enter a numerical value.\n";
        clear_input_buffer();
        cout << "Enter expected annual rate of return: ";
    }

    if (rate < 0) {
        cout << "Warning: Rate cannot be negative. Defaulting to 5%.\n";
        rate = 5.0;
    }
    return rate / 100.0; // Convert percentage to decimal
}

/**
 * Prompts for payment timing, defaulting to "end" for invalid inputs.
 */
string get_payment_timing() {
    string timing;
    cout << "Are payments made at the 'beginning' or 'end' of each period? ";
    cin >> timing;
    
    timing = to_lowercase(timing);
    if (timing != "beginning" && timing != "end") {
        cout << "Warning: Invalid timing. Defaulting to 'end'.\n";
        timing = "end";
    }
    return timing;
}

// --- Core Logic ---

/**
 * Calculates the required recurring payment based on the Time Value of Money formulas.
 */
double calculate_pmt(double current_savings, double future_goal, double rate, int years, const string& timing) {
    // Edge case: 0% interest rate
    if (rate == 0.0) {
        return (future_goal - current_savings) / years;
    }

    // Standard TVM Formula breakdown
    double compound_factor = pow(1 + rate, years);
    double fv_of_current = current_savings * compound_factor;
    
    double rate_factor = (compound_factor - 1) / rate;
    if (timing == "beginning") {
        rate_factor *= (1 + rate); // Adjustment for Annuity Due
    }

    return (future_goal - fv_of_current) / rate_factor;
}

// --- Main Program ---

int main() {
    // 1. Announce the program variant
    cout << "=========================================================\n";
    cout << "This program will calculate recurring payments (PMT).\n";
    cout << "=========================================================\n\n";

    // 2. Gather Inputs & Apply Immediate Termination Rules
    double current_savings = get_monetary_input("Enter current savings already saved (USD): $");
    if (current_savings < 0) {
        cout << "Error: Current savings cannot be negative. Terminating program.\n";
        return 1;
    }

    double future_goal = get_monetary_input("Enter target future value goal (USD): $");
    if (future_goal <= current_savings) {
        cout << "Error: Future goal must be greater than current savings. Terminating program.\n";
        return 1;
    }

    double rate = get_annual_rate();

    int years;
    cout << "Enter number of years to save: ";
    while (!(cin >> years)) {
        cout << "Invalid input. Please enter an integer.\n";
        clear_input_buffer();
        cout << "Enter number of years to save: ";
    }
    
    if (years <= 0) {
        cout << "Error: Number of years must be strictly positive. Terminating program.\n";
        return 1;
    }

    string timing = get_payment_timing();

    // 3. Perform Calculation
    double payment = calculate_pmt(current_savings, future_goal, rate, years, timing);

    // 4. Output Results
    cout << fixed << setprecision(2);
    cout << "\n---------------------------------------------------------\n";
    cout << "Required recurring payment: $" << payment << " per year\n";
    cout << "---------------------------------------------------------\n";

    return 0;
}
