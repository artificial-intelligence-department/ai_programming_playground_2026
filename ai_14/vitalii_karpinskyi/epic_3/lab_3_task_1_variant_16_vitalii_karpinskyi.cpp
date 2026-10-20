#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    // Ініціалізація змінних
    double a = M_PI / 5;
    double b = M_PI;
    double h = (b - a) / 10;
    int n = 40;
    double eps = 0.0001;

    cout << fixed << setprecision(5);
    cout << left << setw(12) << "X" 
         << setw(12) << "SN" 
         << setw(12) << "SE" 
         << setw(12) << "Y" << endl;
    for (double x = a; x <= b + 0.00001; x += h) {
        // Точне Y
        double Y = pow(M_PI, 2) / 8 - (M_PI / 4) * x;

        //  Сума 40 елементів
        double SN = 0.0;
        for (int k = 1; k <= 40; k++){
            SN += cos((2 * k - 1) * x) / pow(2 * k - 1, 2);

        }
        // Сума з точністю до eps
        double SE = 0.0;
        int k = 1;
        double elem = cos((2 * k - 1) * x) / pow(2 * k - 1, 2);
        while (fabs(elem) >= eps) {
            SE += elem;
            k++;
            elem = cos((2 * k - 1) * x) / pow(2 * k - 1, 2);
        }
        cout << left << setw(12) << x 
         << setw(12) << SN 
         << setw(12) << SE 
         << setw(12) << Y << endl;
    }
    
    return 0;
}
