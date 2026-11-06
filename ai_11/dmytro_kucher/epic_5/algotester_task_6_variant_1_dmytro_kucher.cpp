/*
Епік 5. Завдання з Алготестера. Лабораторна робота №6. Завдання №1. Варіант №1
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include <iostream>
#include <string>
using namespace std;

void quicksort(string* arr, int left, int right) {

    int i = left;
    int j = right;
    string pivot = arr[left+(right-left)/2];

    while (i <= j) {

        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;

        if (i <= j) {
            string temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            i++;
            j--;
        }
    }

    if (left < j) quicksort(arr, left, j);
    if (i < right) quicksort(arr, i, right);
}

void func (string word) {

    bool letters[26] = {false};
    int count = 0;

    for (int i = 0; i<word.length(); i++) {
        int index = word[i] - 'a';

        if (!letters[index]) {
            letters[index] = true;
            count++;
        }
    }

    cout << count << "\n";

    for (int i = 25; i>=0; i--) {
        if (letters[i]) {
            cout << char('a' + i);
            count--;

            if (count > 0) cout << " ";
        }
    }
    cout << "\n";
}

int main() {

    int N, K;
    cin >> N >> K;

    string* words = new string[N];

    for (int i = 0; i<N; i++) {
        cin >> words[i];

        for (int j = 0; j<words[i].length(); j++) {
            if (words[i][j] >= 'A' && words[i][j] <= 'Z') words[i][j] += 32;
        }
    }

    quicksort(words, 0, N-1);

    bool letters[26] = {false};
    bool found = false;

    int count = 1;

    for (int i = 0; i<N; i++) {

        if (i+1<N && words[i] == words[i+1]) count++;

        else {
            if (count >= K) {

                found = true;

                for (int j = 0; j < words[i].length(); j++) {
                    letters[words[i][j] - 'a'] = true;
                }
            }

            count = 1;
        }
    }

    if (!found) cout << "Empty!\n";

    else {
        string result = "";

        for (int i = 0; i<26; i++) {
            if (letters[i]) result += char('a' + i);
        }

        func(result);
    }

    delete[] words;

    return 0;
}
