/*  
Задача: Тренер слонів
Карпінський Віталій
СШІ-14
*/

#include <iostream>
using namespace std;

int main () {
    // Вхідні дані
    long long n = 0;
    long long x = 0;
    cin >> n;
    cin >> x;
    long long min = x;
    long long max = x;
    // Обчислення кроків
    for (int i = 1; i < n; i++) {
        cin >>  x;
        if (x < min) {
            min = x;
        }    
        if (x > max) {
            max = x;
        }
    }
    long long result = max - min;
    cout << result;
    return 0;    
}