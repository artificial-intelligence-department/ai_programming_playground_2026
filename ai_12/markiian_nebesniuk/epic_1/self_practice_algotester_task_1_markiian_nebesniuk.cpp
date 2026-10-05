#include <iostream>
using namespace std;

int main() {
    int n;
    int k = 0;
    cin >> n;

    while (n >= 500) {
        n = n - 500;
        k++;
    }

    while (n >= 200) {
        n = n - 200;
        k++;
    }

    while (n >= 100) {
        n = n - 100;
        k++;
    }

    while (n >= 50) {
        n = n - 50;
        k++;
    }

    while (n >= 20) {
        n = n - 20;
        k++;
    }

    while (n >= 10) {
        n = n - 10;
        k++;
    }

    while (n >= 5) {
        n = n - 5;
        k++;
    }

    while (n >= 2) {
        n = n - 2;
        k++;
    }

    while (n >= 1) {
        n = n - 1;
        k++;
    }
    
    cout << k << endl;
    
    return 0;

}