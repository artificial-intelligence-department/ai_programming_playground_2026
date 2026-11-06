/*
Задача Алготестер "Космозаправки"
Небеснюк Маркіян
ШІ-12
*/
#include <iostream>
using namespace std;

// Перевірка, чи є число простим
bool prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int a;
    int b;
    int k;
    cin >> a >> b >> k;

    // Масив з усіма координатами від a до b
    int s[b - a + 1];
    for (int i = 0; i <= b - a; i++) {
        s[i] = a + i;
    }

    int bad[b - a + 1];
    for (int i = 0; i <= b - a; i++) {
        bad[i] = -1;
    }

    int m = 0; // Покриті точки
    int last = -1; // Останній вже зафарбований індекс
    
    // Перевірка простих чисел у діапазоні, що може дістати до [a, b]
    for (int p = a - k; p <= b + k; p++) {
        if (prime(p) == true) {
            // Переведення зони покриття [p-k, p+k] в індекси масиву
            int from = p - k - a;
            int to   = p + k - a;

            // Обрізання зони за межами масиву
            if (from < 0) from = 0;
            if (to > b - a) to = b - a;

            // Пропуск вже зафарбованих елементів
            if (from <= last) from = last + 1;
            for (int j = from; j <= to; j++) {
                bad[j] = 1;
            }
           
            if (to > last) last = to;
        }
    }
    // Підрахунок кількості покритих точок
    for (int i = 0; i <= b - a; i++) {
        if (bad[i] != -1) {
            m++;
        }
    }
    // Загальна кількість мінус покриті
    int result = b - a + 1 - m;
    cout << result << endl;
    
    return 0;
}