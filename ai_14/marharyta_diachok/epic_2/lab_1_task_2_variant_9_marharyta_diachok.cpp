/* 
Задача: Лабораторна робота №1. Завдання 2. Варіант №9. 
Автор: Дячок Маргарита.
Група: ШІ-14
*/

#include <iostream>
#include <string>

using namespace std;
int main() {
int n = 0;
int m;
cout << "Введіть значення n (ціле число): ";
cin >> n;
cout << "Введіть значення m (ціле число): ";
cin >> m;
cout << "Дія №1: ++n*++m.\n";
int first = ++n * ++m;
cout << "Результат: " << first << endl;
cout << "Дія №2: m++<n.\n";
bool second = m++ < n;
string result_1;
if (second == 0) {
    result_1 = "false";
} else {result_1 = "true";}
cout << "Результат: " << result_1 << endl;
cout << "Дія №3: n++ > m.\n";
bool third = n++ > m;
string result_2;
if (third == 0) {
    result_2 = "false";
} else {result_2 = "true";}
cout << "Результат: " << result_2 << endl;


    return 0;
}