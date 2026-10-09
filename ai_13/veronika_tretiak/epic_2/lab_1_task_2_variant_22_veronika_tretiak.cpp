#include <iostream>
using namespace std;

int main(){
//Введення змінних
int n, m;

//Виводимо запит на введення значень n та m
cout << "Введіть значеня n: ";
cin >> n;
cout << "Введіть значення m: ";
cin >> m;


//Обчислюємо значення виразів
int r1 = ++n * ++m;
bool r2 = m++ < n;
bool r3 = n++ > m;

//Виводимо результати обчислень
cout << "1) ++n * ++m = " << r1 << endl;
cout << "2) m++ < n = " << r2 << endl;
cout << "3) n++ > m = " << r3 << endl;

    return 0;
}