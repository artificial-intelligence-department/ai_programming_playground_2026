/*
Algotester Лабораторна робота №4, Завдання №3, Варіант №2.
Цебуля Вадим
ШІ-12
*/
#include <iostream>

using namespace std;

// Швидке сортування (опорний елемент — середній)
void quickSort(int *a, int lo, int hi){
        if (lo >= hi) return;

        int pivot = a[(lo + hi) / 2];
        int i = lo, j = hi;

        while (i <= j){
                while (a[i] < pivot) i++;
                while (a[j] > pivot) j--;
                if (i <= j){
                        int temp = a[i];
                        a[i] = a[j];
                        a[j] = temp;
                        i++;
                        j--;
                }
        }

        quickSort(a, lo, j);
        quickSort(a, i, hi);
}

int main(){
        int n, k;
        cin >> n >> k;

        int a[1005];
        for (int i = 0; i < n; i++){
                cin >> a[i];
        }

        // Швидке сортування, O(n log n)
        quickSort(a, 0, n - 1);

        // Прибирання дублікатів: однакові числа стоять поруч,
        // тому порівнюємо з останнім залишеним
        int m = 1;
        for (int i = 1; i < n; i++){
                if (a[i] != a[m - 1]){
                        a[m] = a[i];
                        m++;
                }
        }

        k %= m;   // обертання на m дає той самий масив

        // Вивід з обертанням вліво на k: result[i] = a[(i + k) % m]
        cout << m << endl;
        for (int i = 0; i < m; i++){
                cout << a[(i + k) % m] << (i + 1 < m ? " " : "");
        }
        cout << endl;

        return 0;
}