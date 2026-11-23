/*
Алготестер лабораторна №6 варіант 1
Небеснюк Маркіян
ШІ-12
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

// Глобальний масив, щоб 100 000 рядків не переповнили стек пам'яті
string words[100005];

int main() {
    // Прискорюємо роботу cin/cout для великої кількості даних (до 10^5 слів)
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> words[i];
        // Переводимо слово в малі літери
        for (size_t j = 0; j < words[i].length(); j++) {
            words[i][j] = (char)tolower((unsigned char)words[i][j]);
        }
    }

    // Сортуємо слова за алфавітом
    sort(words, words + n);

    // Масив-позначка для 26 літер (спочатку всі false)
    bool used[26] = {false};

    int count = 1;
    for (int i = 0; i < n; i++) {
        if (i + 1 < n && words[i] == words[i + 1]) {
            // Наступне слово таке саме — збільшуємо лічильник
            count++;
        } else {
            // Група однакових слів закінчилася — перевіряємо, чи їх >= k
            if (count >= k) {
                for (size_t j = 0; j < words[i].length(); j++) {
                    used[words[i][j] - 'a'] = true;
                }
            }
            // Скидаємо лічильник для наступного нового слова
            count = 1;
        }
    }

    // Рахуємо, скільки унікальних літер ми відмітили
    int m = 0;
    for (int i = 0; i < 26; i++) {
        if (used[i] == true) {
            m++;
        }
    }

    // Вивід результату
    if (m == 0) {
        cout << "Empty!" << endl;
    } else {
        cout << m << endl;
        bool first = true;
        // Ідемо від 25 ('z') до 0 ('a'), щоб отримати зворотний алфавітний порядок
        for (int i = 25; i >= 0; i--) {
            if (used[i] == true) {
                if (first == false) {
                    cout << " ";
                }
                cout << (char)('a' + i);
                first = false;
            }
        }
        cout << endl;
    }

    return 0;
}