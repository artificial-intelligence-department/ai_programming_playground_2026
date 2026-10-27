#include <iostream>
using namespace std;

const int MAX_SIZE = 50;

int sumBelowMainDiagonal(int size, int matrix[][MAX_SIZE]) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < i; j++) {
            sum += matrix[i][j];
        }
    }
    return sum;
}
void output(int size, int matrix[][MAX_SIZE]){
    for(int i=0;i<size;i++){
        cout<<"\n";
        for(int j=0;j<size;j++){
            cout<<matrix[i][j]<<" ";
        }
    }
}

int main() {
    int n, size;

    cout << "Введіть кількість матриць (n): ";
    cin >> n;

    cout << "Введіть розмірність матриць (k <= " << MAX_SIZE << "): ";
    cin >> size;

    if (n <= 0 || size <= 1) {
        cout << "Помилка: кількість матриць має бути > 0, а розмірність > 1." << endl;
        return 1;
    }

    int matrix[MAX_SIZE][MAX_SIZE];
    int maxSum = 0;
    int bestMatrixIndex = 1;

    for (int k = 0; k < n; k++) {
        cout << "\nВведіть елементи матриці #" << (k + 1) << " (" << size << "x" << size << "):\n";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cin >> matrix[i][j];
            }
        }

        int currentSum = sumBelowMainDiagonal(size, matrix);
        output(size, matrix);
        cout << "\nСума елементів нижче головної діагоналі: " << currentSum << endl;


        if (k == 0 || currentSum > maxSum) {
            maxSum = currentSum;
            bestMatrixIndex = k + 1;
        }
    }


    cout << "\nМаксимальна сума елементів нижче головної діагоналі: " << maxSum << endl;
    cout << "Номер матриці з максимальною сумою: #" << bestMatrixIndex << endl;
    

    return 0;
}