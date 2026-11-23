/*
Algotester Лабораторна робота №4, Завдання №2, Варіант №2.
Цебуля Вадим
ШІ-12
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
        int n, k;
        cin >> n >> k;

        vector<int> a(n);
        for (int i = 0; i < n; i++){
                cin >> a[i];
        }

        // unique прибирає лише сусідні повтори, тому спочатку сортуємо
        sort(a.begin(), a.end());
        // unique зсуває унікальні на початок, erase відрізає хвіст
        a.erase(unique(a.begin(), a.end()), a.end());

        int m = a.size();
        k %= m;   // обертання на m дає той самий масив

        // обертання вліво: елемент a[k] стає першим
        rotate(a.begin(), a.begin() + k, a.end());

        cout << m << endl;
        for (int i = 0; i < m; i++){
                cout << a[i] << (i + 1 < m ? " " : "");
        }
        cout << endl;

        return 0;
}