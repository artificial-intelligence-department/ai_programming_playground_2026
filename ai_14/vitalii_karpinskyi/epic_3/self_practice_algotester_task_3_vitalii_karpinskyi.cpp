/*
Задача: Зуби
Карпінський Віталій
СШІ-14
*/
#include <iostream>

using namespace std;

int main() {

    int n;
    int k;
    int array[100000] = {0};
    cin >> n;
    cin >> k;
    int current = 0;
    int max = 0;
    for (int i = 0; i < n; i++) cin >> array[i];

    for (int i = 0; i < n; i++) {
        if (array[i] >= k) {
            current++;
            if (current > max) {
                max = current;
            }  
        } else {
            current = 0;
        }

    }
    cout << max;

    return 0;
}