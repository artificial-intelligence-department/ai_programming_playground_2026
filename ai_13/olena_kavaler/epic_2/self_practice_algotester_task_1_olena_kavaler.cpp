/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <iostream>
#include <cmath> 

using namespace std;

int main() {
    int n;
    cin >> n; // скільки буде дільниць
    int x1, y1, x2, y2; // координати дільниці та представництва

    long long sum = 0; 

    for (int i = 0; i < n; i++) {
        cin >> x1 >> y1 >> x2 >> y2; 
        int dx = x2 - x1; 
        int dy = y2 - y1; 
        double s = sqrt(dx * dx + dy * dy); // відстань за Піфагором
        s = round(s); // округлюємо, щоб 4.9999 не стало 4
        sum += s; 
    }

    cout << sum << endl; 

    return 0;
}
