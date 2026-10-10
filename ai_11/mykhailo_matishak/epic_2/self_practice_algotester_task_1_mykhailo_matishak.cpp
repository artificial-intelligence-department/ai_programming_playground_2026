#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n; 

    long long prev;
    cin >> prev;  

    int cur = 1; // довжина поточного зростаючого підмасиву
    int best = 1;  // найдовша знайдена довжина (мінімум 1)

    for (int i = 1; i < n; i++) {   
        long long x;
        cin >> x;  // 

        if (x > prev) {   // строго більший за попередній?
            cur++;   // так: продовжуємо зростаючу послідовність
        } else {
            cur = 1;    // ні: послідовність обірвалась, починаємо з 1
        }

        if (cur > best) {   // якщо поточна довша за рекорд
            best = cur;             // оновлюємо рекорд
        }

        prev = x;  
    }

    cout << best << endl;   // виводимо довжину найдовшого підмасиву
    return 0;
}