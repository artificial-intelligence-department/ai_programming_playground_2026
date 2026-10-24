// Лабораторна робота 5 Варіант 9
// Стехнович Андрій ШІ-11
#include <iostream>
using namespace std;
float SumUnderMain(float *matrix, int n, int m) {
    int m_end=1;
    float sum = 0;
    for (int i = 1; i<n; i++) {
        for (int j = 0; j<m_end; j++) {
            sum+= *(matrix+m*i+j);

        }
        m_end++;
    }
    return sum;
    
}
int  main(){
    int quantity;
    cout << "Введіть кількість матриць: "<<endl;
    cin >> quantity;
    float res[quantity] = {0};
    for (int i = 0; i<quantity; i++) {
        int n;
        cout << "===================================\nВведіть кількість рядків: ";
        cin >> n;
        cout << "Введіть кількість cтовпців: ";
        int m;
        cin >> m;
        cout << "Введіть матрицю: "<<endl;
        float array [n][m];
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                float a;
                cin >> a;
                array[i][j]=a;
            }
        }
        res[i] = SumUnderMain(*array, n, m);
        cout << endl;
        cout << "Сума елементів під головною діагоналлю: " << res[i] << endl;
    }
    float maxres=res[0];
    for (float a : res) {
        if (a>maxres) {
            maxres=a;
        }
    }
    cout << "=============================\nMaximum sum: " << maxres << endl;
    return 0;
}