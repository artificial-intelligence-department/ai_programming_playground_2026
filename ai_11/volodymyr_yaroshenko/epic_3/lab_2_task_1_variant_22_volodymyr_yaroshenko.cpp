/*  
Лабораторна 2 завдання 1
Варіант 22 
Ярошенко Володимир 
11 група 
*/
#include <iostream> 
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
long double a = 0; // Оголошуєм змінну а
for(int i = 2; i <=16; i++ ) { // Ми починаєм відлік з 2 члена адже при і = 1 або і = 0 функція невизначена
   a += (pow(i, log(i)))/(pow(log(i), i)); 
} 
cout << setprecision(6) << a << endl; // виводим результат з точністю до 4 знака після коми
return 0;
}