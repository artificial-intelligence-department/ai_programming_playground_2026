#include <iostream>

using namespace std;

int sum(int** a, int x, int y){ // сума підмасиву 3 на 3 з лівим верхнім кутом x, y

    int s = 0;

    for (int i = x; i < x + 3; i++){
        for (int j = y; j < y + 3; j++){
            s += a[i][j]; // додаємо елемент до суми
        }
    }

    return s;
}

int main(){

    int n,m; // розміри масиву

    cin >> n >> m;

    int** a = new int*[n]; // двовимірний масив
    for (int i = 0; i < n; i++){
        a[i] = new int[m];
    }

    for (int i = 0; i < n; i++){ // заповнюємо масив
        for (int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }

    if (n < 3 || m < 3){ // підмасив 3 на 3 не поміщається
        cout << "Масив надто маленький";
    }
    else{
        int mx = sum(a, 0, 0); // максимальна сума для початку, бо не можна починати з нуля(якщо наприклад всі від'ємні)
        int x = 0; // рядок кута найкращого підмасиву
        int y = 0; // стовпець кута найкращого підмасиву

        for (int i = 0; i <= n - 3; i++){ // перебираємо всі ліві верхні кути
            for (int j = 0; j <= m - 3; j++){
                int s = sum(a, i, j); // сума поточного підмасиву
                if (s > mx){ // знайшли більшу суму
                    mx = s;
                    x = i;
                    y = j;
                }
            }
        }

        cout << "Максимальна сума: " << mx << endl;
        cout << "Найкращий верхній лівий кут: рядок " << x + 1 << ", стовпець " << y + 1 << endl;

        for (int i = x; i < x + 3; i++){ // друк знайденого підмасиву
            for (int j = y; j < y + 3; j++){
                if (j > y) { cout << " ";}
                cout << a[i][j];
            }
            cout << endl;
        }
    }

    for (int i = 0; i < n; i++){ // звільняємо пам'ять
        delete[] a[i];
    }
    delete[] a;

return 0;
}