/*
    Задача: Верховна Рада
    Автор: Нагірний Назарій
    Група: СШІ-13
*/
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    long long a[n];
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    
    long long d = a[0];
    for (int i = 1; i < n; i++) {
        long long x = d;
        long long y = a[i];
        
        while (y != 0) {
            long long temp = y;
            y = x % y;
            x = temp;
        }
        d = x;
    }
    long long min = sum / d;
    cout << min << "\n";
    return 0;
}