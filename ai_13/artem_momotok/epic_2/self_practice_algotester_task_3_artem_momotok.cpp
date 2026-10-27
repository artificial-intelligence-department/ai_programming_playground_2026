/*
Верховна Рада, Артем Момоток, ШІ-13
*/
#include <iostream>
using namespace std;

int main() {

    int n; // Кількість партій в Верховній раді
    cin >> n;

    long long d = 0, sum = 0; // d - НСД (найбільший спільний дільник), sum - сума потрібних місць для партій 
    for (int i = 0; i < n; i++) {
        long long x; 
        cin >> x; 
        sum += x; 

        // Обчислюємо НСД між поточним значенням d і числом x ( кількості учасників партії)
        long long a = d, b = x;
        while (b != 0) {
            long long t = a % b; 
            a = b; 
            b = t; 
        }
        d = a; 
    }

    cout << endl; 
    cout << sum / d << endl; // Виводимо кількість місць, які потрібно виділити для всіх партій

    return 0;
}