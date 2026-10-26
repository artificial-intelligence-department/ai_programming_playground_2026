#include <iostream>

using namespace std;

int main(){

    int a[10005];

    int n = 0;
    while (cin >> a[n]){
        n++;
    }

    for (int i = 1; i < n; i++){
        int key = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > key){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }

    for (int i = 0; i < n; i++){
        cout << a[i] << (i == n - 1 ? "" : " ");
    }

    return 0;
}
