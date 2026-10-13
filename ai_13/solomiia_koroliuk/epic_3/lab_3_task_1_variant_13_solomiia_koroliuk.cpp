#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
    double a = 0.2;
    double b = 1.0;
    int k = 10;
    int n = 10;
    double eps = 0.0001;

    double h = (b - a) / k;

    cout << fixed << setprecision(6);

    for (int i = 0; i <= k; i++){

        double x = a + i * h; // 0.2 <= x <= 1
        double t = (x - 1.0) / (x + 1.0);


        // Додавання членів ряду до суми SN 
        double SN = 0.0;
        double term = t;

        for (int j = 0; j < n; j++){
            SN += term; 
            term = term * t * t * (2.0 * i + 1) / (2.0 * i + 3); // Рекурентна формула
        
        }


        // Обчислення суми SE із заданою точністю
        double SE = 0.0;
        term = t;
        int j = 0;

        while (abs(term) >= eps){

            SE += term;
            term = term * t * t * (2.0 * i + 1) / (2.0 * i + 3);

            j++;
        }

        // Точне значення функції
        double Y = 0.5 * log(x);
        cout << "X = " << setw(10) << x << "  SN = " << setw(10) << SN << "  SE = " << setw(10) << SE << "  Y = " << setw(10) << Y << endl; 

    }

    return 0;
}
