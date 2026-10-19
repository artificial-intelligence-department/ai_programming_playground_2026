/*
Задача: Найбільша зростаюча послідовність
Карпінський Віталій
СШІ-14
*/
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    long a[100] = {0};
    long copy[100] = {0};
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        copy[i] = 1;
    }
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
        if (a[j] < a[i]) {
            if (copy[j] + 1 > copy[i]) {
                copy[i] = copy[j] + 1;
            }
        }
    }
}
    int result = 0;
    for (int i = 0; i < n; i++) {
        if (copy[i] > result) {
            result = copy[i];
        }
    }
cout << result << endl;
    return 0;
}