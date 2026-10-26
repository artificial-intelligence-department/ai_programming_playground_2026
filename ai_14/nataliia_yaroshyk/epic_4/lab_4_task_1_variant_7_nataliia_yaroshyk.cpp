/*  Лабораторна робота 4v7
    Ярошик Наталія
    ШІ-14 */
#include <iostream>
#include <cstdlib> // Для rand() і srand()
#include <ctime> // Для time()
using namespace std;

int main(){
    int N = 100;
    int n;
    int a[N] = {};
    cout << "Введіть розмір масиву: ";
    if(!(cin >> n) || n > N){
        cout << "Розмір масиву завеликий" << endl;
        return 0;
    }else{
        N = n;
    }

    srand(time(0));

    for(int i = 0; i < N; i++){
        a[i] = rand() % 11;
    }

    cout << "Отриманий масив" << endl;
    for(int i = 0; i < N; i++){
        cout << a[i] << " ";
    }
    cout << endl;

    for(int i = N - 1; i >= 0; i--){
        if(a[i] == 0){
            for(int j = i; j < N - 1; j++){
                a[j] = a[j + 1];
            }
            N--;
            break;
        }
    }

    cout << "Після якого індекса елемента додати елемент 100?" << endl;
    int el;
    cin >> el;
    if(el >= 0 && el < N){
        for(int i = N; i > el + 1; i--){
            a[i] = a[i - 1];
        }
    }else{
        cout << "Введено некоректний індекс\n";
        return 0;
    }
    a[el + 1] = 100;
    N++;
    
    cout << "Отриманий масив" << endl;
    for(int i = 0; i < N; i++){
        cout << a[i] << " ";
    }
    return 0;
}