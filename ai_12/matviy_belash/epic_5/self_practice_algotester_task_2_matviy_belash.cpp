/*
Белаш Матвій ШІ-12
Завдання з алготестеру "Снігурочка"
*/
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {

    string word;
    int k = 0;

    while (cin >> word) {
        for (int i = 0; i < word.length(); i++) {
            word[i] = tolower(word[i]);
        }
        bool palid = true;
        int n = word.length();
        for (int i = 0; i < n / 2; i++) {
            if (word[i] != word[n - i - 1]) {
                palid = false;
                break;
            }
        }

        if (palid) {
            k++;
        }
    }

    cout << k << endl;

    return 0;
}