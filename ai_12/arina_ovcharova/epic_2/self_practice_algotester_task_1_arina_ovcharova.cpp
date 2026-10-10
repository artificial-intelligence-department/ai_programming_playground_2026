#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    int l[20], r[20];

    // Зчитуємо відрізок для кожного покемона
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
    }

    int points[20];

    // Зчитуємо можливі точки тренування
    for (int i = 0; i < m; i++) {
        cin >> points[i];
    }

    // Відповідь не перевищує 2^15 - 1, тому взяття за модулем 10^9+7 не потрібне
    int answer = 0;

    // Перебираємо всі непорожні підмножини покемонів
    for (int mask = 1; mask < (1 << n); mask++) {
        int left = -1000000000;
        int right = 1000000000;

        // Знаходимо спільний відрізок
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                if (l[i] > left)
                    left = l[i];

                if (r[i] < right)
                    right = r[i];
            }
        }

        // Перевіряємо, чи є дозволена точка
        // всередині спільного відрізка
        for (int j = 0; j < m; j++) {
            if (points[j] >= left && points[j] <= right) {
                answer++;
                break;
            }
        }
    }

    cout << answer;

    return 0;
}
