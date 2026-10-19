/*
self practice task 2, Веселі каруселі
*/
#include <iostream>
using namespace std;
int main (){
    int k, n;
    cin >> k >> n;
    int C[n];
    for(int i=0; i<n; i++){//ввід множини
        cin >> C[i];
    }
    for (int i = 0; i < n-1; i++){ // bubble sort за допомогою вкладеного циклу
        for (int j = 0; j < n-i-1; j++){
            if (C[j] > C[j + 1]){// умова перестановки
                double tempVal = C[j]; // створюю тимчасове значення, щоб не втратити старе значення C[j]
                C[j] = C[j + 1];
                C[j + 1] = tempVal;
            }
        }}
        int count = 0;
    for(int i=0; i<n; i++){//цикл витрат 
        if(k<C[i]){//перевірка чи вистачає грошей
            break;
        }else{
        k-=C[i];
        count++;
        }
    }
    cout << count;
    return 0;
}