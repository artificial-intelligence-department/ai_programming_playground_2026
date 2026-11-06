#include <iostream>
using namespace std;

/*
 * Задача: Lab 4 Task 1-21
 * Щербак Орислав
 * Група ШІ-11
 */

 const int N = 100;

int main(){
    int a[N];
    int n, k;
    cout << "Введіть кількість елментів(1-96): ";
    if(!(cin >> n) || n < 1 || n > 96){
        cout << "Помилка, кількість елментів повинна бути від 1 до 96.";
        return 1;
    }
    cout << "Введіть елементи масиву: ";
    for(int i = 0; i < n; i++){
        if(!(cin >> a[i])){
            cout << "Помилка введення.";
            return 1;
        }
    }
    cout << "Введіть К: ";
    if(!(cin >> k) || k < 1 || k > n){
        cout << "Помилка, кількість елментів повинна бути від 1 до " << n << ".";
        return 1;
    }
    int index = k - 1;
    for(int i = 0; i < n; i++){
        cout << a[index] << " ";
        --index;
        if(index < 0){
            index = n - 1;
        }
    }
    cout << endl;
    int first, last1, last2, last3;
    cout << "Введіть новий перший елемент: ";
    if(!(cin >> first)){
        cout << "Помилка вводу." << endl;
        return 1; 
    }
    cout << "Введіть нові три останні елементи: ";
    if(!(cin >> last1 >> last2 >> last3)){
        cout << "Помилка вводу." << endl;
        return 1; 
    }
    for(int i = n; i > 0; i--){
        a[i] = a[i-1];
    }
    a[0] = first;
    ++n;
    a[n] = last1;
    ++n;
    a[n] = last2;
    ++n;
    a[n] = last3;
    ++n;
    cout << "Масив після додавання: " << endl;
    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl;
    index = k - 1;
    for(int i = 0; i < n; i++){
        cout << a[index] << " ";
        ++index;
        if(index == n){
            index = 0;
        }
    }
    return 0;
}