/*
Назва: Цікавий масив
Автор: Бичковський Володимир
Група: ШІ-11
*/

#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int* arr = new int [n];

    for(int i=0; i<n; i++){
        cin >> arr[i];
    }

    int sum = 0;
    int sum1 = 0;
    for(int i=0; i<n-1; i++){
        sum = 0;
        for(int j = i + 1; j<n; j++){
            sum += arr[j];
        }
        sum1 += arr[i];
        if(sum == sum1){
            cout << "TAK";
            delete[] arr;
            return 0;
        }
    }
    cout << "NI";
    delete[] arr;
}