/*
self practice task 1, Зима
*/
#include <iostream>
using namespace std;
int main(){
    int A[3];
    int a;
    for(int i = 0; i<3; i++){//циклом ввожу змінні
        cin >> a;
        A[i] = a;
    }
    for (int i = 0; i < 2; i++){ // bubble sort за допомогою вкладеного циклу
        for (int j = 0; j < 2 - i; j++){
            if (A[j] < A[j + 1]){// умова перестановки
                double tempVal = A[j]; // створюю тимчасове значення, щоб не втратити старе значення A[j]
                A[j] = A[j + 1];
                A[j + 1] = tempVal;
            }
        }}
        int sum = A[1] + A[2];
        cout << sum;
    return 0;
}