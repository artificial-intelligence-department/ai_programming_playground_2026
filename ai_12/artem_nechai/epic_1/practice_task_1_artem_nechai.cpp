/*
Задача: Автономність портативної зарядної станції
Прізвище: Нечай
Номер групи: ШІ-12
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {    cout << "1.Enter model name(no spaces, for example: Battery_123): ";
    string modelName;
    cin >> modelName;
    cin.clear();
    cin.ignore(256, '\n');

    cout << "2. Enter battery capacity in Wh (range: 0-5000) (for example: 2000): ";
    double capacity;
    cin >> capacity;
    while (cin.fail() || 5000 < capacity || capacity < 0) {
        cout << "Error" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> capacity;
    }

    cout << "3. Enter battery age in years (range: 0-20) (for example: 2): ";
    int age;
    cin >> age;
    while (cin.fail() || 20 < age || age < 0) {
        cout << "Error" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> age;
    }

    cout << "4. Enter battery charge in percentage (range: 0-100) (for example: 80): ";
    double charge;
    cin >> charge;
    while (cin.fail() || 100 < charge || charge < 0) {
        cout << "Error" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> charge;
    }
    // Transform charge percentage to decimal
    charge *= 0.01;

    cout << "5. Enter invertor coefficient of performance (range: 0-100) (for example: 85): ";
    double cop;
    cin >> cop;
    while (cin.fail() || 100 < cop || cop < 0) {
        cout << "Error" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> cop;
    }
    // Transform cop percentage to decimal
    cop *= 0.01;

    cout << "6. Enter battery power (range: 0-500) (for example: 100): ";
    double power;
    cin >> power;
    while (cin.fail() || 500 < power || power < 0) {
        cout << "Error" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> power;
    }

    // Calculate real capacity by applying degradation factor per year, // where 0.98 is the degradation factor per year(2% per year): 1 - 0.02 = 0.98
    double real_capacity = capacity * pow(0.98, age);

    // Calculate energy stored by multiplying real capacity by charge percentage
    double energy_stored = real_capacity * charge;

    // Calculate available energy by multiplying energy stored by invertor coefficient of performance(cop)
    double energy_available = energy_stored * cop;

    // Calculate energy loss by subtracting energy output from energy stored
    double energy_loss = energy_stored - energy_available;

    // Calculate working time by dividing available energy output by power
    double working_time = energy_available / power;

    // Convert working time to hours by factoring out only integer part
    int hours = static_cast<int>(working_time);

    // Convert working time to minutes by multiplying the floor part by 60
    int minutes = static_cast<int>((working_time - hours) * 60);

    cout << fixed << setprecision(1);
    cout << endl << "Battery has following specifications:" << endl
        << "Battery model:      " << modelName << endl
        << "Battery age:        " << age << " years" << endl
        << "Real capacity:      " << real_capacity << " Wh" << endl
        << "Battery charge:     " << charge * 100 << "%" << endl
        << "Invertor cop:       " << cop * 100 << "%" << endl
        << "Energy stored:      " << energy_stored << " Wh" << endl
        << "Available energy:   " << energy_available << " Wh" << endl
        << "Energy loss:        " << energy_loss << " Wh" << endl
        << "Working time:       " << hours << " hours and " << minutes << " minutes" << endl;

    return 0;
}