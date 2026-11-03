/*Лабораторна робота 4 варіант 17
Ім'я: Сукач Андрій
Група: ШІ-14*/

#include <iostream>

using namespace std;
int main(){
    const int maximum = 100;
    int a[maximum];
    int n, k;
    int new_first, new_last;
    cin >> n;
    cin >> k;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
cout << endl;
cout << endl;
    // Роздрукувати отриманий масив, починаючи з К-ого елемента й до К-1 (по кільцю вліво).
    for (int i = 0; i < n; i++) {
    cout << a[(k - i + n) % n] << " ";
}

    cin >> new_first >> new_last;

    for (int i = n; i > 0; i--) {// зсуваємо елементи масиву вправо для вільної комірки
        a[i] = a[i - 1];
    }

    a[0] = new_first; // додаємо перший елемент на початок масиву
    n++;

    a[n] = new_last; // додаємо останнній елемент в кінець масиву
    n++;

     // Роздрукувати отриманий масив, починаючи з К-ого елемента й до К+1 (по кільцю вправо).
    for (int i = 0; i < n; i++) {
    cout << a[(k + i + n) % n] << " ";
}
cout << endl;
    return 0;
}

