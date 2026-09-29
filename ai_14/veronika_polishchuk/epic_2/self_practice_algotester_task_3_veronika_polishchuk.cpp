/*
 * Задача: Зуби (алготестер додатково)
 * Поліщук Вероніка
 * Група 14
 */
#include <iostream>

using namespace std;
int main() {
    int n, k, a;
    cin >> n >> k;
    int count=0, max_count= 0;

    for (int i = 0; i < n; i++){
        cin >> a;
        if (a >= k) {
            count++;
            if (count > max_count) max_count = count;
        }
        else count = 0;
    }
    cout << max_count;
    return 0;
}
