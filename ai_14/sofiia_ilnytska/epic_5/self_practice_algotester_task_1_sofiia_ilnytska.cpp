/*
   Задача: Снігурочка (алготестер)
   Ільницька Софія
   Група ШІ-14
*/

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string word;
    int count = 0;  // Лічильник слів-паліндромів

    // Зчитуємо слова до кінця вводу
    while (cin >> word) {
        bool palindrome = true;
        int n = word.length();

        // Порівнюємо символи з початку та кінця слова
        for (int i = 0; i < n / 2; i++) {
            // Порівнюємо символи без урахування регістру
            if (tolower(word[i]) != tolower(word[n - 1 - i])) {
                palindrome = false;
                break;
            }
        }

        if (palindrome) {
            count++;
        }
    }

    cout << count << endl;

    return 0;
}
