/*Автономність портативної зарядної станції, Тимофієнко, ШІ-14*/
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

int main(){
    string station_model;
    double nominal_capacity;
    double years;
    double degradation;
    double current_charge;
    double efficiency;
    double power_consumption;

    cout << "Enter station model: ";
    cin>>station_model;
    if (station_model.length()>31){
        cout<<"Error: Station model name must not exceed 31 symbols."<<endl;
        return 1;
    }
    
    cout << "Enter nominal battery capacity (Wh):";
    cin >> nominal_capacity;
    if (nominal_capacity<=0) {
        cout <<"Error: Capacity must be greater than 0." <<endl;
        return 1;
    }
    cout << "Enter years of operation: ";
    cin >> years;
    if (years <0 || years>20){
        cout <<"Error: Years must be between 0 and 20." <<endl;
        return 1;
    }
    cout << "Enter annual degradation rate (e.g., 0.02): ";
    cin >> degradation;

    cout << "Enter current charge level (%): ";
    cin >> current_charge;
    if (current_charge <0|| current_charge>100){
        cout <<"Error: Charge must be between 0 and 100."<<endl;
        return 1;
    }

    cout << "Enter system efficiency (%): ";
    cin >> efficiency;
    if (efficiency<=0 || efficiency>100){
        cout<<"Error: Efficiency must be between 0 and 100."<<endl;
        return 1;
    }
    cout << "Enter power consumption (W): ";
    cin >> power_consumption;
    if (power_consumption<=0) {
        cout<<"Error: Power consumption must be greater than 0."<<endl;
        return 1;
    }

    double base = 1.0 - (degradation/100.0);
    double aged_capacity = nominal_capacity * pow(base, years);
    double E_stored = aged_capacity * (current_charge/100.0);
    double E_useful = E_stored * (efficiency/100.0);
    double E_loss = E_stored - E_useful;
    double T = E_useful/power_consumption;
    int h = static_cast<int>(T);
    int m = static_cast<int>((T-h)*60);

    cout<<"\n--- Calculation Results ---\n";
    cout <<left<<setw(30)<<"Model:"<<station_model<<endl;

    cout<<fixed;
    cout<<setw(30)<<"Nominal Capacity (Wh):"<<setprecision(1)<<nominal_capacity<<endl;
    cout<<setw(30)<<"Age (years):"<<setprecision(0)<<years<<endl;
    cout<<setw(30)<<"Aged Capacity (Wh):"<<setprecision(1)<<aged_capacity<<endl;
    cout<<setw(30)<<"Current Charge (%):"<<setprecision(0)<<current_charge<<endl;
    cout<<setw(30)<<"Efficiency (%):"<<setprecision(2)<<efficiency<<endl;
    cout<<setw(30)<<"Stored Energy (Wh):"<<setprecision(1)<<E_stored<<endl;
    cout<<setw(30)<<"Useful Energy (Wh):"<<setprecision(1)<<E_useful<<endl;
    cout<<setw(30)<<"Energy Losses (Wh):"<<setprecision(1)<<E_loss<<endl;

    cout<<setw(30)<<"Operation Time:"
    <<setprecision(2)<<T<<"hours = "
    <<h<<"hours"<< (m<10? "0":"")<<m<<"min"<<endl;











    
}