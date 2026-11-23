/*
Задача Алготестер "Примітивна довга арифметика"
Небеснюк Маркіян
ШІ-12
*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    long long x, n, k;
    cin >> x >> n >> k;

    string ans = "";
    long long carry = 0; // перенос у наступний розряд

    // Усього стовпчиків (без фінального переносу): n + k - 1
    for (long long p = 0; p < n + k - 1; p++) {
        // Рахуємо, скільки чисел дотягуються до стовпчика p
        long long left = max(0LL, p - n + 1);
        long long right = min(k - 1, p);
        long long cnt = right - left + 1;

        long long sum = cnt * x + carry;
        ans += (char)('0' + (sum % 10)); // остання цифра йде у відповідь
        carry = sum / 10;                // решта йде в перенос
    }

    // Якщо після всіх стовпчиків ще залишився перенос — дописуємо його
    while (carry > 0) {
        ans += (char)('0' + (carry % 10));
        carry /= 10;
    }

    // Ми записували цифри справа наліво, тому перевертаємо рядок
    reverse(ans.begin(), ans.end());

    cout << ans << endl;
    return 0;
}