
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string words[100000];

void quickSort(string words[], int left, int right) {
    int i = left;
    int j = right;
    string pivot = words[(left + right) / 2];

    while (i <= j) {
        while (words[i] < pivot) {
            i++;
        }

        while (words[j] > pivot) {
            j--;
        }

        if (i <= j) {
            string temp = words[i];
            words[i] = words[j];
            words[j] = temp;
            i++;
            j--;
        }
    }

    if (left < j) {
        quickSort(words, left, j);
    }

    if (i < right) {
        quickSort(words, i, right);
    }
}

int main() {
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> words[i];

        for (int j = 0; j < words[i].length(); j++) {
            words[i][j] = tolower(words[i][j]);
        }
    }

    quickSort(words, 0, n - 1);

    bool letters[26] = {false};
    int count = 1;

    for (int i = 1; i <= n; i++) {
        if (i < n && words[i] == words[i - 1]) {
            count++;
        } 
        else {
            if (count >= k) {
                string word = words[i - 1];

                for (int j = 0; j < word.length(); j++) {
                    letters[word[j] - 'a'] = true;
                }
            }

            count = 1;
        }
    }

    int m = 0;

    for (int i = 0; i < 26; i++) {
        if (letters[i]) {
            m++;
        }
    }

    if (m == 0) {
        cout << "Empty!";
        return 0;
    }

    cout << m << '\n';

    for (int i = 25; i >= 0; i--) {
        if (letters[i]) {
            cout << char('a' + i) << ' ';
        }
    }

    cout << '\n';

    return 0;
}
