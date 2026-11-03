#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int odd_count = 0, even_count = 0;
    int* a = new int[n];
    int* even = new int[n];
    int* odd = new int[n];

    for (int i = 0; i < n; ++i) {
        int temp;
        cin >> temp;
        a[i] = temp;
    }

    for (int i = 0; i < n; ++i) {
        if (a[i] % 2 == 0) {
            even[even_count] = a[i];
            ++even_count;
        } else {
            odd[odd_count] = a[i];
            ++odd_count;
        }
    }

    if (!(even_count == odd_count ||
          even_count - 1 == odd_count ||
          even_count == odd_count - 1)) {
        cout << -1 << '\n';

        delete[] a;
        delete[] even;
        delete[] odd;

        return 0;
    }

    if (even_count == odd_count) {
        for (int i = 0; i < even_count; ++i) {
            cout << even[i] << " " << odd[i] << " ";
        }
    } else if (even_count > odd_count) {
        for (int i = 0; i < even_count; ++i) {
            if (i == even_count - 1) {
                cout << even[i];
                break;
            }

            cout << even[i] << " " << odd[i] << " ";
        }
    } else if (odd_count > even_count) {
        for (int i = 0; i < odd_count; ++i) {
            if (i == odd_count - 1) {
                cout << odd[i];
                break;
            }

            cout << odd[i] << " " << even[i] << " ";
        }
    }


    delete[] a;
    delete[] even;
    delete[] odd;

    return 0;
}