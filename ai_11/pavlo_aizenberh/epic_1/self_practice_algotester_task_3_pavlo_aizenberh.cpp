/* Задача №0021:
Вхідні дані
У єдиному рядку задано одне натуральне число amount — вартість подарунку.

Вихідні дані
У єдиному рядку виведіть одне ціле число — мінімальну кількість купюр, що необхідна для покупки подарунка.*/

#include <iostream>
using namespace std;

int main(){
    int amount;
    cin >> amount;
    int count = 0;
    while (amount != 0){
    if (amount >= 500){
        amount -= 500;
        count += 1;
    }
    else if (amount >= 200){
        amount -= 200;
        count += 1;
    }
    else if (amount >= 100){
        amount -= 100;
        count += 1;
    }
    else if (amount >= 50){
        amount -= 50;
        count += 1;
    }
    else if (amount >= 20){
        amount -= 20;
        count += 1;
    }
    else if (amount >= 10){
        amount -= 10;
        count += 1;
    }
    else if (amount >= 5){
        amount -= 5;
        count += 1;
    }
    else if (amount >= 2){
        amount -= 2;
        count += 1;
    }
    else if (amount == 1){
        amount -= 1;
        count += 1;
    }
    }
    cout << count << endl;
    return 0;
}