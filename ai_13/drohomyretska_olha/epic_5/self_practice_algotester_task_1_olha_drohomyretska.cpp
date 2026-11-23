/*
Задача: Марічка вмикає лампи
Автор: Ольга Дрогомирецька
Група: ШІ-13
*/
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;

    //обчислюємо відповідь за формулою
    double result = (m + 1.0) / (m - n + 1.0);
    
    cout << fixed << setprecision(10) << result << "\n";
    return 0;
}