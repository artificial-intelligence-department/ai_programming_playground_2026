/*
Назва задачі: Цікавий масив
Автор: Лисюк Андріана
Група: ШІ-13
*/

#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int array[100];
    for (int i = 0; i < n; i++) {
        cin >> array[i];
    }

    for (int k = 1; k < n; k++) {
        int sum_before_k = 0;
        int sum_after_k = 0;
        for (int j = 0; j < k; j++) {
            sum_before_k += array[j];
        }
        for (int m = k; m < n; m++) {
            sum_after_k += array[m];
        }
        if (sum_before_k == sum_after_k) {
            cout << "TAK";
            return 0;
        }
    }
    cout << "NI";
    return 0;
}
