/* Лабораторна робота 3, Варіант 11, Андрій Шикоряк */
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    const double epsilon = 0.0001;
    double a = 0.1;
    double b = 1.0;
    int steps = 10;
    double move = (b - a) / steps;


    cout << fixed << setprecision(5);
    cout << "   X     " << "     SN        " << "    SE           " << "   Y" << endl;
  

    for (double x = a; x <= b + 0.00001; x += move)
    {
        double Y = (1.0 + 2.0 * (x * x)) * exp(x * x);
        double SN = 1.0; 
        double an_n = 1.0; 
        for (int i = 0; i < 9; i++)
        {
            an_n *= (x * x * (2 * i + 3)) / ((i + 1) * (2 * i + 1));
            SN += an_n;
        }
        // РОзрахунок суми ряду з точністю e = 0.0001
        double SE = 1.0;   
        double an_e = 1.0;  
        
        for (int j = 0; an_e >= epsilon; j++)
        {
            an_e *= (x * x * (2 * j + 3)) / ((j + 1) * (2 * j + 1));
            SE += an_e;
        }
        cout << x << "     " << SN << "     " << SE << "        " << Y << endl;
    }
    return 0;
}
