#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
/*
Лабароторна робота 2, Варіант 17, Андрій Шикоряк

Умова
Знайти суму рядку з точністю e = 0.0001
Формула an = 10^n-1 * (n-1)!
Формула рекурентного вигляду = an+1 = an * n / 10
a1 = 0.1

*/
int main() {
    const double epsilon = 0.0001; 
    double sum = 0.0;        
    int n = 1;             
    double a =0.1;       
    
    while (a >= epsilon) {
        sum += a;         
        a = a * n / 10.0;    
        n++;
    }
    cout << "Сума послідовності: " << fixed << setprecision(5) << sum <<endl;
    cout << "Кількість ітерацій: " << n - 1 << endl;

    return 0;
}
