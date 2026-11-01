/*
self-practice algotester task 1 Найбільша зростаюча послідовність, Андрій Мадяр
*/
#include <iostream>
using namespace std;
int main(){
    int n = 0, maxLen = 1;
    cin >> n;
    int *arr = new int[n];//
    int *currMaxLen = new int[n];//для перевірки найдовшої
    for(int i = 0; i<n;i++){
        cin >> arr[i];
        currMaxLen[i]=1;
    }
    for(int i = 0; i<n; i++){
        for(int j = 0; j<i; j++){
//перевіряємо кожен елемент і на наявність перед ним елемента j на послідовність довжина якої >= довжини послідовності елемента і
            if(arr[i] > arr[j]){//в цьому випадку елемент і МОЖЕ стати новим елементом послідовності елемента j
            if(currMaxLen[j]+1 > currMaxLen[i])currMaxLen[i] = currMaxLen[j]+1;//елемент і стає новим елементом посладовності елемента j
            }
        }
        if(currMaxLen[i] > maxLen)maxLen = currMaxLen[i];//нам треба лише найбільшу з них
    }
    cout << maxLen;
    delete[] arr;
    return 0;
}