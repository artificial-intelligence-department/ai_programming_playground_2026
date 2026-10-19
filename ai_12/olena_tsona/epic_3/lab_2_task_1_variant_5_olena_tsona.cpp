/*Lab 2 Task 1 Variant 5
Цьона Олена
ШІ-12 */

#include <iostream>
#include <cmath>

using namespace std;
 
int main()
{
    double eps = 0.0001;    // задана точність епселонт
    double S = 0;           // сума ряду
    int n = 1;              // номер поточного доданка
    double dodanok = 1;     // доданок 
 
    while (fabs(dodanok) >= eps)
    {
        S = S + dodanok;
        dodanok = -dodanok * pow(n, n) / pow(n + 1, n + 1);
        n++;
    }
 
    cout << "Сума ряду з точністю 0.0001" << endl;
    cout << "S = " << S << endl;
    cout << "Кількість доданків: " << n - 1 << endl;
 
    return 0;
}