/*Задача Lab 6v1
Виконавець: Сукач Андрій
СШІ-14*/
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

void quickSort(string *s, int left, int right);

int main() {
    int n, k;
    cin >> n >> k;

    string *s = new string[n];
    for (int i = 0; i < n; i++) {
        cin >> s[i];

        for (int j = 0; j < (int)s[i].length(); j++) { // перевід в нижній регістр
            s[i][j] = tolower((unsigned char)s[i][j]);
        }
    }

    if (n > 0) {
        quickSort(s, 0, n - 1);
    }

    bool found_letters[26] = {false};
    int unique_letters_count = 0;

    int word = 0;
    while (word < n) {
        int j = word;
        // Рахуємо, скільки разів підряд повторюється однакове слово s[word]
        while (j < n && s[j] == s[word]) {
            j++;
        }
        int word_count = j - word;

        if (word_count >= k) {
            // Беремо кожну букву цього слова
            for (int i = 0; i < (int)s[word].length(); i++) {
                char c = s[word][i];
                int index = c - 'a'; // Перетворюємо букву на індекс від 0 до 25

                if (index >= 0 && index < 26 && !found_letters[index]) {
                    found_letters[index] = true;
                    unique_letters_count++;
                }
            }
        }

        word = j; // Переходимо до наступної групи слів
    }

    if (unique_letters_count > 0) {
        // Виводимо кількість унікальних букв
        cout << unique_letters_count << "\n";

        // Виводимо букви у зворотному порядку: від 'z' (індекс 25) до 'a' (індекс 0)
        bool first = true;
        for (int c = 25; c >= 0; c--) {
            if (found_letters[c]) {
                if (!first) {
                    cout << " ";
                }
                cout << (char)('a' + c);
                first = false;
            }
        }
        cout << "\n";
    } else {
        cout << "Empty!\n";
    }

    delete[] s;
    return 0;
}

void quickSort(string *s, int left, int right) {
    int i = left, j = right;
    string centre = s[(left + right) / 2];

    while (i <= j) {
        while (s[i] < centre) i++;
        while (s[j] > centre) j--;
        if (i <= j) {
            string temp = s[i];
            s[i] = s[j];
            s[j] = temp;
            i++;
            j--;
        }
    }
    if (left < j) quickSort(s, left, j);
    if (i < right) quickSort(s, i, right);
}