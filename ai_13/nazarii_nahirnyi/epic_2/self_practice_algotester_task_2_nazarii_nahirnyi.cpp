/*
    Задача: Борщ, картопля і салат
    Автор: Нагірний Назарій
    Група: СШІ-13
*/
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int main(){
    int n;
    if (!(cin >> n)) return 0;
    long a[n], b[n], c[n];
    for (int i = 0; i < n; i++){
        cin >> a[i] >> b[i] >> c[i];
    }
    sort(a, a + n);
    sort(b, b + n);
    sort(c, c + n);
    long suma = a[n / 2];
    long sumb = b[n / 2];
    long sumc = c[n / 2];
    long total_sum = 0;
    for (int i = 0; i < n; i++){
        total_sum += abs(suma - a[i]);
        total_sum += abs(sumb - b[i]);
        total_sum += abs(sumc - c[i]);
    }
    
    cout << total_sum << "\n";
    
    return 0;
}
