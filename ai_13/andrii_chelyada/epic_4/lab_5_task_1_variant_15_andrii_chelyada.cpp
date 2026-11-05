// lab 5 task 1 variant 15 Andrii Chelyada

#include <iostream>
using namespace std;

int findMaxSum(int arr[50][50], int n, int m){
    int maxSum = -1000000000;
    for(int j = 0; j < m - 1; j++){
        int sumJ = 0;
        for(int i = 0; i < n - j - 1; i++){
            sumJ += arr[i][j];
        }
        cout << "Сума стовпця " << j + 1 << ": " << sumJ << endl;
        if (sumJ > maxSum){
            maxSum = sumJ;
        }
    }
    return maxSum;
}

int main(){
    int n; // рядки
    int m; // стовпці
    int arr[50][50];
    cout << "Введіть к-сть рядків: " << endl;
    cin >> n;
    cout << "Введіть к-сть стовпців: " << endl;
    cin >> m;

    if(n <= 0 || n > 50 || m <= 0 || m > 50){
        cout << "Недопустимі розміри масиву" << endl;
        return 0;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << "Введіть значення для матриці: " << "[" << i + 1 << "]" << "[" << j + 1 << "]" << endl;
            cin >> arr[i][j];
        }
    }

    cout << "Матриця:" << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    int maxSum = findMaxSum(arr, n, m);
    cout << "Максимальна сума: " << maxSum << endl;
    
    return 0;
}
