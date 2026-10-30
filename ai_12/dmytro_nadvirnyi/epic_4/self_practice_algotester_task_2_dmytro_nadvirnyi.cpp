//algotester self practice task 2 2042
#include <iostream>
using namespace std;

void processMinesweeper(const char* s, char* result, int n) {
    for (int i = 0; i < n; i++) {
        if (s[i] == '*') {
            result[i] = '*';
        } else {
            int count = 0;

            // Перевірка сусіда зліва
            if (i > 0 && s[i - 1] == '*') {
                count++;
            }

            // Перевірка сусіда справа
            if (i < n - 1 && s[i + 1] == '*') {
                count++;
            }

            result[i] = '0' + count;
        }
    }
    result[n] = '\0'; // позначаємо кінець рядка
}

int main() {
    int n;
    cin >> n;

    // 1. Створюємо динамічні масиви через new
    char* s = new char[n + 1];
    char* result = new char[n + 1];

    // Зчитуємо посимвольно (виправлення помилки GCC 14)
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    s[n] = '\0';

    // 2. Передаємо масиви (вказівники) у функцію
    processMinesweeper(s, result, n);

    // 3. Виводимо результат
    cout << result << "\n";

    // 4. Звільняємо пам'ять 
    delete[] s;
    delete[] result;

    return 0;
}