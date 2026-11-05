#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int arrN[100];
    for (int i = 0; i < n; i++) {
        cin >> arrN[i];
    }
    int m;
    cin >> m;
    int arrM[100];
    for (int i = 0; i < m; i++) {
        cin >> arrM[i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arrN[j] > arrN[j + 1]) {
                int temp = arrN[j];
                arrN[j] = arrN[j + 1];
                arrN[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - 1 - i; j++) {
            if (arrM[j] > arrM[j + 1]) {
                int temp = arrM[j];
                arrM[j] = arrM[j + 1];
                arrM[j + 1] = temp;
            }
        }
    }

    int countSame = 0;
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (arrN[i] == arrM[j]) {
            countSame++;
            i++;
            j++;
        } else if (arrN[i] < arrM[j]) {
            i++;
        } else {
            j++;
        }
    }

    cout << countSame << endl;
    cout << n + m - countSame << endl;
    return 0;
}