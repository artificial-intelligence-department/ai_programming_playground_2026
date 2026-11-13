
/* 
Епік 4. self practice: Algotester, задача "Заповніть сейф"
Авторка: Влада Ташогло
Група: ші-11
*/

#include <iostream>
using namespace std;

const int MAXN = 1000000;

int spf[MAXN + 1]; // Найменший простий дільник

// Решето Ератосфена для швидкої факторизації
void buildSieve() {
    for (int i = 1; i <= MAXN; i++) {
        spf[i] = i;
    }

    for (int i = 2; i * i <= MAXN; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j <= MAXN; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
}

int main() {
    buildSieve();

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        long long N = 1LL * n * m;

        int p2 = 0, p3 = 0;
        int minOther = MAXN + 1; // Найменший простий дільник >= 5
        int minPrime = MAXN + 1; // Будь-який найменший простий дільник

        int a = n;
        int b = m;

        // Факторизація розмірів n та m
        while (a > 1) {
            int p = spf[a];
            minPrime = min(minPrime, p);

            if (p == 2) p2++;
            else if (p == 3) p3++;
            else minOther = min(minOther, p);

            a /= p;
        }

        while (b > 1) {
            int p = spf[b];
            minPrime = min(minPrime, p);

            if (p == 2) p2++;
            else if (p == 3) p3++;
            else minOther = min(minOther, p);

            b /= p;
        }

        // Мінімальна кількість днів (кольорів) q
        long long q;

        if (n == 1 || m == 1) {
            q = minPrime; // Одновимірний сейф
            
            if (q == MAXN + 1) q = 1;
        }
        else {
            // Двовимірний сейф: блок 2x2 вимагає q >= 4
            q = minOther;  
            if (p2 >= 2) q = min(q, 4LL);
            if (p2 >= 1 && p3 >= 1) q = min(q, 6LL);
            if (p3 >= 2) q = min(q, 9LL);
        }
        // Максимальна кількість злитків на день: k = N / q
        cout << N / q << '\n';
    }

    return 0;
}
