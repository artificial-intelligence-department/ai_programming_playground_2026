#include <iostream>
#include <algorithm>
using namespace std;
//задає уомву для sort()
bool comesBefore(int a, int b) {
    if (a % 3 != b % 3) {
        return a % 3 < b % 3;
    }
    if (a % 3 == 1) {
        return a > b;
    }
    return a < b;
}
//сортує
void sortToThree(int* arr, int& n) {
    sort(arr, arr + n, comesBefore);
    n = unique(arr, arr + n) - arr;
}
int main() {
    int n;
    cin >> n;

    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    sortToThree(arr, n);
    //вивід
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << arr[i];
    }
    cout << '\n';

    delete[] arr;
    arr = nullptr;
    return 0;
}