/*
    Алготестер. "Найбільша зростаюча підпослідовність"
    Гончаренко Семен
    ШІ-11
*/
#include <iostream>

using namespace std;

int main() {
    int n = 0;
    cin >> n;
    
    int a[100] = {0}; // declaring empty array (max 100)
    for (int i = 0; i < n; i++) { // filling empty array
        cin >> a[i];
    }
    
    int temp[100] = {0}; // declaring empty array for temporary elements
    int sum = 0; // declaring variable for sum
    
    for (int i =0; i < n; i++) {
        temp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                if (temp[j] + 1 > temp[i]) {
                    temp[i] = temp[j] + 1;
                }
            }
        }
        if (temp[i] > sum) {
            sum = temp[i];
        }
    }
    cout << sum << endl;
return 0;
}