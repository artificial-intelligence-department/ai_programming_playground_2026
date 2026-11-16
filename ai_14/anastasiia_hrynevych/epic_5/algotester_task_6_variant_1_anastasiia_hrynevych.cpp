#include <iostream>
#include <cstring>
using namespace std;

void swap(string &a, string &b) {
    string temp = a;
    a = b;
    b = temp;
}

void heapify(string arr[], int n, int i) {
    int largest = i; 
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapsort(string arr[], int n) {
    for (int i = n/2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    int n, k; cin >> n >> k;
    string *words = new string[n];
    for (int i = 0; i < n; i++) {
        cin >> words[i];
        for (int j = 0; j < words[i].length(); j++) {
            int ch = words[i][j];
            if (ch >= 'A' && ch <= 'Z') {
                ch += 32;
            }
            words[i][j] = ch;
        }
    }
    bool present[26] = {false};
    heapsort(words, n);
    int count = 1;
    for (int i = 0; i < n; i++) {

    if (i == n - 1 || words[i] != words[i + 1]) {
        if (count >= k) {
            for (int j = 0; j < words[i].length(); j++) {
                present[words[i][j] - 'a'] = true;
            }
        }
        count = 1; 
    } else {
        count++; 
    }
}

    int m = 0;
    for (int i = 0; i < 26; i++) {
        if (present[i]) m++;
    }
    if (m == 0) {
        cout << "Empty!" << endl;
        return 0;
    }
    cout << m << endl;
    for (int i = 25; i >= 0; i--) {
        if (present[i]) {
            cout << (char)('a' + i) << " ";
        }
    }
    cout << endl;
    delete[] words;
    words = nullptr;
    return 0;
}