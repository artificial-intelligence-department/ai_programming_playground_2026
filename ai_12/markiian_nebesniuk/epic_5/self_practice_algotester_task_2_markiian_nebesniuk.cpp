/*
Задача Алготестер "Снігурочка"
Небеснюк Маркіян
ШІ-12
*/
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Перевірка, чи є слово паліндромом без урахування регістру
bool isPalindrome(const string &word) {
    int left = 0;
    int right = (int)word.length() - 1;

    // Йдемо двома вказівниками з обох кінців слова до середини
    while (left < right) {
        char c1 = (char)tolower((unsigned char)word[left]);
        char c2 = (char)tolower((unsigned char)word[right]);

        if (c1 != c2) {
            return false;
        }
        left++;
        right--;
    }

    return true;
}

int main() {
    string word;
    int count = 0;

    // cin >> word автоматично пропускає пробіли та переноси рядків
    // і читає слова до самого кінця вхідних даних (EOF)
    while (cin >> word) {
        if (isPalindrome(word) == true) {
            count++;
        }
    }

    cout << count << endl;
    return 0;
}