/*Задача:Існує дві дороги: Одна пряма, а інша …(алготестер)
виконав: Сукач Андрій*/

#include <iostream>
#include <cmath> 

using namespace std;

int main() {
   
    int n;
    if (!(cin >> n)) return 0;

    long long total = 0;

    for (int i = 0; i < n; i++) {//цикл для всіх n
        long long x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        // Знаходжу різницю координат
        long long dx = x2 - x1;
        long long dy = y2 - y1;
        //формула з геометрії (теорема Піфагора)
        // round() гарантує точне ціле число без похибок дробових обчислень
        total += round(sqrt(dx * dx + dy * dy));
    }

    cout << total;

    return 0;
}