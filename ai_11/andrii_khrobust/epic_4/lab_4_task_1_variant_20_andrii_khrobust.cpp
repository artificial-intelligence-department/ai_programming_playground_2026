#include <iostream>
using namespace std;

int main() {
    int n;
    int a[2000];
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int K;
    cout << "Введіть K (від 1 до "<<n<<"): ";
    cin >> K;
    if (K < 1 || K > n) {
        cout << "Погане K";
        return 0;
    }
    // 1. Виведення по кільцю вліво від K до K-1
    cout << "Вліво:" << endl;
    for (int i = 0; i < n; i++) {
        int j = (K - 1 - i + n) % n;
        cout << a[j] << " ";
    }
    cout << endl;
    // 2. Вставлення 0 після елементів з індексами, кратними 5
    int save = n;
    for (int i = save - 1; i >= 0; i--) {
        if (i % 5 == 0) {
            for (int j = n; j > i + 1; j--) {
                a[j] = a[j - 1];
            }
            a[i + 1] = 0;
            n++;
        }
    }
    // 3. Виведення по кільцю вправо від K
    cout << "Вправо:" << endl;
    int start = (K - 1) % n;

    for (int i = 0; i < n; i++) {
        int j = (start + i) % n;
        cout << a[j] << " ";
    }
    cout << endl;
    return 0;
}