/*
Олексійчук Захар
Загадай число
*/

#include <iostream>
#include <cstring>
using namespace std;

void FillArray(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        cin >> *(arr+i);
    }
}

int main() {
    int n, la, lb;
    cin >> n >> la >> lb;
    int* a = new int[la];
    int* b = new int[lb];

    FillArray(a, la);
    FillArray(b, lb);

    bool* has_rem = new bool[n + 1](); 
    int* modified_indices = new int[lb];
    int success_p = 0;

    for (int p = 1; p <= n; p++) {
        int modified = 0;
        bool isFound = false;

        for (int j = 0; j < lb; j++) {
            if (b[j] == 0) continue;
            int rem = p % b[j];
            if (!has_rem[rem]) {
                has_rem[rem] = true;
                modified_indices[modified++] = rem;
            }
        }

        for (int i = 0; i < la; i++) {
            if (a[i] == 0) continue;
            int div = p / a[i];
            if (has_rem[div]) {
                isFound = true;
                break;
            }
        }

        if (isFound) success_p++;

        for (int i = 0; i < modified; i++) {
            has_rem[modified_indices[i]] = false;
        }
    }

    cout << success_p << endl;

    delete[] a;
    delete[] b;
    delete[] has_rem;
    delete[] modified_indices;
    return 0;
}

// bool pFound = false;
// int success_p = 0;
// int p = 1;
// while(p <= n){
//     for (int i = 0; i < la; i++) {
//         for (int j = 0; j < lb; j++) {
//             if ((p / a[i]) == (p % b[j])) {
//                 pFound = true;
//                 break;
//             }
//             if (pFound) break;
//         }
//     }
//     if (pFound) {
//         success_p++;
//         pFound = false;
//     }
//     p++;
// }
// cout << success_p << endl;