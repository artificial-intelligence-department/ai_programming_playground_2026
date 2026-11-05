/*лабораторна робота з алготестеру #5 v2*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void create(int n, int k, int m[100][100]){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < k; j++){
            m[i][j] = rand() % 100;
        }
    }
}
void swapRows(int m[100][100], int first, int second, int k){
    for(int j = 0; j < k; j++){
        int temp = m[first][j];
        m[first][j] = m[second][j];
        m[second][j] = temp;
    }
}
void sorting(int m[100][100], int n, int k){
    for(int i = 0; i < n-1; i++){
        for(int q = 0; q < n-i-1; q++){
            if(m[q][2] > m[q+1][2]){
                swapRows(m, q, q+1, k);
            }
        }
    }
}
void print(int m[100][100], int n, int k){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < k; j++){
            cout << m[i][j] << "\t";
        }
        cout << endl;
    }
}

int main(){
    int n, k, m[100][100];

    cout << "Введіть кількість рядків та стовпців масиву: ";
    cin >> n >> k;
    if (cin.fail() || n < 1 || n > 100 || k < 3 || k > 100){
        cout << "Введіть дійсні значення";
        return 1;
    }
    srand(time(0));

    create(n, k, m);
    cout << "Початковий масив:\n";
    print(m, n, k);
    sorting(m, n, k);
    cout << "Відсортований масив за третім стовпцем:\n";
    print(m, n, k);
    return 0;
}
