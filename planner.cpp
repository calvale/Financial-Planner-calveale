/*
 * Author: Aleena Calvert
 * File: planner.cpp
 * Description: Calculates recurring payments needed
 * to reach a future savings goal.
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cctype>

using namespace std;

/*
 * Makes the timing lowercase.
 */
string make_lowercase(string word) {

    for (int i = 0; i < word.length(); i++) {
        word.at(i) = tolower(word.at(i));
    }

    return word;
}

/*
 * Gets the annual return rate.
 */
double get_rate() {

    double rate;

    cout << "Enter annual return rate as a percent: ";
    cin >> rate;

    if (rate < 0) {
        cout << "Invalid rate. Using 5% instead." << endl;
        rate = 5;
    }

    return rate / 100;
}

// Gets payment timing
string get_timing() {

    string timing;

    cout << "Are payments made at the beginning or end of each period? ";
    cin >> timing;

    timing = make_lowercase(timing);

    // if invalid
    if (timing != "beginning" && timing != "end") {
        cout << "Invalid timing. Using end instead." << endl;
        timing = "end";
    }

    return timing;
}

// Calcs recurring payment
double calculate_payment(double current_savings, double future_goal, double rate, int years, string timing) {

    double payment;

    // If rate zero
    if (rate == 0) {
        payment = (future_goal - current_savings) / years;
    }

    // Norm formula
    else {

        double top;
        double bottom;

        top = future_goal -
              current_savings * pow(1 + rate, years);

        bottom =
        (pow(1 + rate, years) - 1) / rate;

        // Adjustment for beginning payments
        if (timing == "beginning") {
            bottom = bottom * (1 + rate);
        }

        payment = top / bottom;
    }

    return payment;
}

int main() {

    double current_savings;
    double future_goal;
    double rate;
    double payment;

    int years;

    string timing;

    cout << "This program will calculate recurring payments."
         << endl;

    // For current savings
    cout << "Enter current savings: ";
    cin >> current_savings;

    // Checks for invalid savings
    if (current_savings < 0) {
        cout << "Error: current savings cannot be negative."
             << endl;
        return 1;
    }

    // future goal
    cout << "Enter future value goal: ";
    cin >> future_goal;

    // is goal is valid?
    if (future_goal <= current_savings) {
        cout << "Error: future goal must be greater than current savings."
             << endl;
        return 1;
    }

    rate = get_rate();

    cout << "Enter number of years to save: ";
    cin >> years;

    // are years valid
    if (years <= 0) {
        cout << "Error: years must be greater than zero."
             << endl;
        return 1;
    }

    timing = get_timing();

    // Calcs payment
    payment = calculate_payment(current_savings, future_goal, rate, years, timing);

    cout << fixed << setprecision(2);

    cout << "Required recurring payment: $"
         << payment << endl;

    return 0;
}
