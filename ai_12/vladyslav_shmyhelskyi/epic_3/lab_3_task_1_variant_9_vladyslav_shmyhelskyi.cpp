#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{

    const double e = 0.0001;
    const double a = 0.1;
    const double b = 0.8; // вводимо константи
    double y;
    for (double x = a; x <= b; x += 0.07)
    {
        y = 1.0 / 4.0 * log((1 + x) / (1 - x)) + 1.0 / 2.0 * atan(x);//рахуємо Y прямо, підставляючи всі x по черзі у формулу
        double x4 = x * x * x * x;
        double c = x; 
        double SN = x;  // Сумма починається з x;
        for (int n = 1; n <= 3; n++)
        {
            c = c * x4; // рекурентна формула для численьика 
            double total = c / ((4 * n) + 1); //знаменник залишаємо звичайним 
            SN += total;
        }
        c = x; // обнуляємо змінні для наступного циклу
        double total = c / 1.0;
        double SE = 0;
        int n = 0;
        while (total >= e) //Шукаємо суму,поки вона не буде меншою ε 
        { 
            SE += total;
            n++;
            c = c * x4;
            total = c / ((4 * n) + 1);
            
        }

        cout << fixed << setprecision(2) << "X = " << x << endl;
        cout << fixed << setprecision(6) << "SN = " << SN << endl;
        cout << fixed << setprecision(6) << "SE = " << SE << endl;
        cout << fixed << setprecision(6) << "Y = " << y << endl;
    }

    return 0;
}