/*Лабораторна 4, варіант 3. Задача: розподіл масиву за остачею від ділення на 3
Автор: Матішак Михайло
Група: ШІ-11*/
#include <iostream>

using namespace std;

struct Number{
    int value;
    int rem;
};

int main(){
    Number a[1000];
    Number b[1000];
    int n;
    int k = 0;

    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> a[i].value;
        a[i].rem = a[i].value % 3;
    }

    for(int r = 0; r < 3; r++){
        for(int i = 0; i < n; i++){
            if(a[i].rem == r){
                b[k] = a[i];
                k++;
            }
        }
    }

    for(int i = 0; i < k - 1; i++){
        for(int j = 0; j < k - 1 - i; j++){
            bool swapIt = false;

            if(b[j].rem == b[j + 1].rem){
                if(b[j].rem == 1 && b[j].value < b[j + 1].value){
                    swapIt = true;
                }
                if(b[j].rem != 1 && b[j].value > b[j + 1].value){
                    swapIt = true;
                }
            }

            if(swapIt){
                Number temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;
            }
        }
    }

    int d = 0;
    for(int i = 0; i < k; i++){
        bool found = false;
        for(int j = 0; j < d; j++){
            if(b[j].value == b[i].value){
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
        cout << b[i].value << " ";
    }
    cout << endl;

    return 0;
}