#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    // обчислюємо перший член за початковою формулою (підставляємо 1 )
    double a = 1.0 / exp(1.0);
    double summa = a; // ініціалзуємо суму і даємо їй значення першого члена
    for (int n = 1; n < 7; n++)
    {
        // обчислюємо коефіцієнт (відношення ratio = a(n+1) / an):
        double ratio = pow((double)(n + 1) / n, 2) * (exp(-sqrt(n + 1)) / exp(-sqrt(n)));
        // Знаходимо наступний член ряду за формулою a(n+1) = an * ratio
        a *= ratio;
        // додаємо цей новий член до суми
        summa += a;

    }
    cout << "Сумма 7 членів прогресії: " << summa << endl;

}