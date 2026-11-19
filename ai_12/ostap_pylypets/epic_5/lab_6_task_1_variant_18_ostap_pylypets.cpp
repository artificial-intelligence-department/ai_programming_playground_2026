#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

int main() {
    char str[256];
    int i = 0 , n = 0, m = 0, pos[130];
    string words[130], dw[130];
    string cur;
    cout << "Input text: ";
    if (!fgets(str, sizeof(str), stdin)) {
        return 0;
    }
    while (str[i] != '\0' && str[i] != '\n' && str[i] != '\r') {
        i++;
    }
    if (i == 0 || str[i - 1] != '.') {
        cout << "Text must end with a period.\n";
        return 1;
    }
    //зберігаємо слова у words
    for (int k = 0; k < i - 1; k++) {
        if (str[k] == ' ') {
            if (!cur.empty()) {
                words[n++] = cur;
                cur.clear();
            }
        } else {
            cur += str[k];
        }
    }
    if (!cur.empty()) {
        words[n++] = cur;
    }
    //записуємо позиції слів
    for (i = 0; i < n; i++) {
        if (words[i][0] >= '0' && words[i][0] <= '9') {
            pos[m] = i;
            dw[m] = words[i];
            m++;
        }
    }
    //сортуємо
    for (i = 0; i < m - 1; i++) {
        for (int k = 0; k < m - 1 - i; k++) {
            if (dw[k] < dw[k + 1]) {
                cur = dw[k];
                dw[k] = dw[k + 1];
                dw[k + 1] = cur;
            }
        }
    }
    //ставимо слово на нову позицію
    for (int k = 0; k < m; k++) {
        words[pos[k]] = dw[k];
    }
    cout << "Output text: ";
    for (i = 0; i < n; i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << words[i];
    }
    cout << ".\n";
    return 0;
}