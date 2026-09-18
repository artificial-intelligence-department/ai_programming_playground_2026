/*
Task name: Автономність портативної зарядної станції
Name: Захар Олексійчук
Group: ШІ-14 (ai_14)
*/

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    // Введення змінних
    string model; //модель
    float C; // ємність
    int years; // вік акумулятора
    int charge; // поточний рівень заряду
    float eff; // ККД інвертора
    int P; // потужність

    const float BASE_CHARGE = 100.0; // базовий рівень заряду
    const float CAPACITY_LOSS = 2.0; // відсоток втрати ємності за рік
    const float MINUTES_IN_HOUR = 60.0; // кількість хвилин в годині 


    // Введення даних та їх валідація
    cout << "=== DATA ENTRY ===\n";

    cout << "Enter charging station model: ";
    if (!(cin >> model) || model.length() > 31) { 
        cout << "Error: Model name is too long (maximum = 31 symbols)\n";
        return 0;
    }

    cout << "Capacity according to passport (watts per hour): ";
    if (!(cin >> C) || C <= 0) {
        cout << "Capacity can't be 0 or less\n";
        return 0;
    }

    cout << "Enter station's age: ";
    if (!(cin >> years) || years < 0 || years > 20) {
        cout << "Age should be in range 0-20\n";
        return 0;
    }

    cout << "Charge percentage (%): ";
    if (!(cin >> charge) || charge < 0 || charge > 100) {
        cout << "Charge should be in range 0-100%\n";
        return 0;
    }

    cout << "Efficiency (%): ";
    if (!(cin >> eff) || eff <= 0 || eff > 100) {
        cout << "Efficiency should be in range 0(excluded) - 100\n";
        return 0;
    }

    cout << "Power (watts): ";
    if (!(cin >> P) || P <= 0) {
        cout << "Power must be above 0\n";
        return 0;
    }

    // обчислення ємності акумулятора після року споживання
    float saved_energy_per_year = 1.0 - (CAPACITY_LOSS / BASE_CHARGE); 

    // Обчислення фактичної ємності після років використання
    float C_eff = C * pow(saved_energy_per_year, years); 

    // Обчислення ємності з урахуванням поточного заряду
    float E_stored = C_eff * (charge / BASE_CHARGE); 
    // Обчислення корисної енергії
    float E_useful = E_stored * (eff / BASE_CHARGE); 
    // Обчислення втраченої енергії
    float E_loss = E_stored - E_useful; 
    float T = E_useful / P; // Час роботи
    int h = (int)T; // Години роботи
    int m = (T - h) * MINUTES_IN_HOUR; // Хвилини роботи

    // Вивід інформації
    cout << "\n=== INFO ABOUT STATION ===\n";
    cout << " - Model: " << model << endl;
    cout << " - Capacity (according to passport): " << fixed << setprecision(1) << C << "w/h" << endl;
    cout << " - Age: " << (int)years << "y." << endl;
    cout << " - Capacity (factual): " << fixed << setprecision(1) << C_eff << "w/h" << endl;
    cout << " - Charge: " << (int)charge << "%" << endl;
    cout << " - EFF: " << fixed << setprecision(2) << eff << "%" << endl;
    cout << " - Saved energy: " << fixed << setprecision(1) << E_stored << "w/h" << endl;
    cout << " - Useful charge: " << fixed << setprecision(1) << E_useful << "w/h" << endl;
    cout << " - Energy loss: " << fixed << setprecision(1) << E_loss << "w/h" << endl;
    cout << " - Working time: " << fixed << setprecision(2) << T << " hours  =  " << h << " hours " << setw(2) << setfill('0') << m << " minutes" << endl;
}