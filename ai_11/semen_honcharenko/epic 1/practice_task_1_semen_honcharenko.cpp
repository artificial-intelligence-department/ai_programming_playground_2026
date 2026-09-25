/*
 * Автономність портативної зарядної станції
 * semen_honcharenko
 * ai_11
 */

#include <iostream> // input/output library
#include <string> // text string library
#include <cmath> // math library
#include <iomanip> // output formatting library

int main() {

    std::string model; // creating "model" variable for name
    std::cout << "Model name: ";
    std::cin >> model; // user input model name
    if (model.length() > 31) { // checking if the model name is longer than 31 characters
        std::cout << "Error. Model name can't be longer than 31 characters." << std::endl; // Error. Model name is too long
        return 1;
    }

    double C; // creating "C" variable for capacity
    std::cout << "Rated capacity of the station (Wh): ";
    std::cin >> C; // user input rated capacity
    if (C <= 0) { // checking if the rated capacity is less than or equal to 0
        std::cout << "Error. Rated must be positive." << std::endl; // Error. Rated capacity is negative
        return 1;
    }

    int years; // creating "years" variable for age
    std::cout << "Age of the station (years): ";
    std::cin >> years; // user input age
    if (years < 0 ||  years > 20) { // checking if age is not lower than 0 and not greater than 20
        std::cout << "Error. Age must be between 0 and 20" << std::endl; // Error. Age is lower than 0 or greater than 20
        return 1;
    }

    int charge; // creating "charge" variable for charge
    std::cout << "Charge of the station (%): ";
    std::cin >> charge; // user input charge
    if (charge < 0 || charge > 100) { // checking if charge is not lower that 0 and not higher than 100
        std::cout << "Error. Charge must be between 0 and 100" << std::endl; // Error. Charge is lower than 0 or higher than 100
        return 1;
    }

    double eff; // creating "eff" variable for efficiency
    std::cout << "Efficiency of the station (%): ";
    std::cin >> eff; // user input efficiency
    if (eff < 0 || eff > 100) { // checking if efficiency is not lower than 0 and not higher than 100
        std::cout << "Error. Efficiency must be between 0 and 100" << std::endl; // Error. Efficiency is lower than 0 or higher than 100
        return 1;
    }

    double P; // creating "P" variable for power
    std::cout << "Power of the station (W): ";
    std::cin >> P; // user input power
    if (P <= 0) { // checking if power is less than or equal to 0
        std::cout << "Error. Power must be positive" << std::endl; // Error. Power is negative
        return 1;
    }

    int h; // Full hours
    int m; // Minutes remaining
    double C_eff; // Actual capacity
    double E_stored; // Energy reserve at current charge
    double E_loss; // Energy conversion losses
    double E_useful; // Useful energy that will reach the device
    double T; // Working time, hours

    const double degeneration_per_year = 2.0; // battery degeration per year
    C_eff = C * pow((1.0 - degeneration_per_year / 100.0), years); 
    
    E_stored = C * (charge / 100.0); 
    E_useful = E_stored * (eff / 100.0); 
    E_loss = E_stored - E_useful;
    T = E_useful / P;
    h = std::trunc(T);
    m = std::trunc((T - h) * 60.0 );
    
    std::cout << "----------------------------------------" << std::endl; // for better result visibility
    std::cout << "Model name: " << model << std::endl; // model output
    std::cout << "Rated capacity: " << trunc(( C / 10.0 ) * 10.0 ) << " Wh" << std::endl; // rated capacity output
    std::cout << "Age: " << years << " years" << std::endl; // age output
    std::cout << "Actual capacity: " << trunc(( C_eff / 10.0 ) * 10.0) << " Wh" << std::endl; // actual capacity output
    std::cout << "Charge: " << charge << " %" << std::endl; // charge output
    std::cout << "Efficiency: " << eff << " %" << std::endl; // efficiency output    
    std::cout << "Stored energy: " << trunc((E_stored / 10.0) * 10.0) << " Wh" << std::endl; // stored energy output
    std::cout << "Useful energy: " << trunc((E_useful / 10.0) * 10.0) << " Wh" << std::endl; // useful energy output 
    std::cout << "Energy loss: " << trunc((E_loss / 10.0) * 10.0) << " Wh" << std::endl; // energy loss output
    std::cout << "Time left: " << (( T / 100.0 ) * 100.0 ) << " h = " << h << "h " << ( m < 10 ? "0" : "") << m << "m" << std::endl;
    return 0;
    
}