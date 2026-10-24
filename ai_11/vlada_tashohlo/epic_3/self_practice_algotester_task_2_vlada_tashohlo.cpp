
/* 
Епік 3. self practice: Algotester, задача "Обернений факторіал"
Авторка: Влада Ташогло
Група: ші-11
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main() {
    
    string s;
    if (!(cin >> s)) return 0;

    // маленькі n: порівнюємо точно
    const string t[10] = {"", "1", "2", "6", "24", "120",
                          "720", "5040", "40320", "362880"};
    for (int n = 1; n <= 9; ++n)
        if (s == t[n]) { cout << n; return 0; }

    long long L = (long long)s.size();

    long double sum = 0.0L;
    for (int i = 1; ; ++i) {
        sum += log10l((long double)i);
        long long d = (long long)floor(sum) + 1;
        if (d == L) { cout << i; return 0; }

    }
}