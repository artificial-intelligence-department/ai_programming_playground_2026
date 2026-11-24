/*Лабораторна 4, варіант 3. Задача: розподіл масиву за остачею від ділення на 3
Автор: Матішак Михайло
Група: ШІ-11*/
#include <iostream>

using namespace std;

int main(){
    int a[1000];
    int ra[1000];
    int b[1000];
    int rb[1000];
    int n;
    int k = 0;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        ra[i] = a[i] % 3;
    }
    for(int r = 0; r < 3; r++){
        for(int i = 0; i < n; i++){
            if(ra[i] == r){
                b[k] = a[i];
                rb[k] = ra[i];
                k++;
            }
        }
    }
    for(int i = 0; i < k - 1; i++){
        for(int j = 0; j < k - 1 - i; j++){
            bool swapIt = false;
            if(rb[j] == rb[j + 1]){
                if(rb[j] == 1 && b[j] < b[j + 1]){
                    swapIt = true;
                }
                if(rb[j] != 1 && b[j] > b[j + 1]){
                    swapIt = true;
                }
            }
            if(swapIt){
                int temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;
            }
        }
    }
    int d = 0;
    for(int i = 0; i < k; i++){
        bool found = false;
        for(int j = 0; j < d; j++){
            if(b[j] == b[i]){
                found = true;
            }
        }
        if(!found){
            b[d] = b[i];
            d++;
        }
    }
    cout << d << endl;
    for(int i = 0; i < d; i++){
        cout << b[i] << " ";
    }
    cout << endl;

    return 0;
}