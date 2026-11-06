/* 
Лабораторна робота н.5
Варіант: 6
Автор: Давидович Святослав
Група: ШІ-11
*/

#include <iostream>
#include <random>
#include <iomanip>

using namespace std;

int main(){
    const int RANGE = 1000;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(0, RANGE);

    // динамічне виділення
    const int N = 4; // для N = 10 випадкова поява сідлових точок малоймовірна, варто дивитися для N = 2,3,4
    int** matrix = new int*[N];
    for (int i = 0; i<N; i++){
        matrix[i] = new int[N];
    }

    // випадкова генерація елементів матриці в діапазоні [0, RANGE]
    for (int i = 0; i<N; i++){
        for (int j = 0; j<N; j++){
            matrix[i][j]=distrib(gen);
        }
    }

    cout << "Матриця:\n";
    for (int i = 0; i<N; i++){
        for (int j = 0; j<N; j++){
            cout << setw(4) << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    
    // 4 масиви для збереження індексів макс./мін. елементів кожного рядка./стовпця
    int* highRows = new int[N];
    int* lowRows = new int[N];
    int* highCols = new int[N];
    int* lowCols = new int[N];

    // пошук для рядків
    for (int i = 0; i<N; i++){
        int max = 0;
        int min = 0;
        for (int j = 0; j<N; j++){
            if (matrix[i][max]<matrix[i][j]) max = j;
            if (matrix[i][min]>matrix[i][j]) min = j;
        }
        highRows[i] = max;
        lowRows[i] = min;
    }
    // пошук для стовпців
    for (int j = 0; j<N; j++){
        int max = 0;
        int min = 0;
        for (int i = 0; i<N; i++){
            if (matrix[max][j]<matrix[i][j]) max = i;
            if (matrix[min][j]>matrix[i][j]) min = i;
        }
        highCols[j] = max;
        lowCols[j] = min;
    }

    cout << "Сідлові точки: \n";
    for (int i = 0; i<N; i++){
        // перевіряємо співпадіння відповідних елементів масиву рядків та стовпців
        if (lowCols[highRows[i]]==i) cout << "(" << i << "," << highRows[i] << ")\n";
        if (highCols[lowRows[i]]==i) cout << "(" << i << "," << lowRows[i] << ")\n";
    }

    // звільнення динамічної пам'яті
    for (int i = 0; i<N; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] highRows;
    delete[] highCols;
    delete[] lowCols;
    delete[] lowRows;
    
    return 0;
}

    
