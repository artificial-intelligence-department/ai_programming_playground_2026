/*
Задача: Снігурочка
Автор: Ольга Дрогомирецька
Група: ШІ-13
*/
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string word;
    int count = 0;

    //читаємо слова з усіх рядків до кінця вводу
    while (cin >> word) {
        int length = word.size();
        bool palindrome = true;

        //порівнюємо букви з початку та кінця слова
        for (int i = 0; i < length / 2; i++) {
            if (tolower(word[i]) != tolower(word[length - 1 - i])) {
                palindrome = false;
                break;
            }
        }
        //якшо слово є паліндромом, збільшуємо лічильник
        if (palindrome) {
            count++;
        }
    }
    cout << count << "\n";
    return 0;
}