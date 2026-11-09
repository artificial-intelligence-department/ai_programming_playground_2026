#include <iostream>

using namespace std;

bool matrix(int a[][100],int n,int m){
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            cin >> a[i][j];
            
            if(cin.fail()) {
                cout << "Помилка введення елементів матриці!";
                return false;
            }
        }
    }
    return true;
}

int findMaxSum (int a[][100],int n,int m){
    int maxSum = 0;
    for(int j = 0;j < m - 1;j++){
        int sum = 0;
        for(int i = 0; i < n - j -1;i++){
            sum += a[i][j];
        }

    if(j == 0){
        maxSum = sum;
    }else if (sum > maxSum){
        maxSum = sum;
    }
    cout << "Сума елементів стовпця " << j + 1 << ": " << sum << endl;
    }


return maxSum;
}

int main(){

int n;
int m;
int a[100][100];

cout << "Введіть к-сть рядків:";
cin >> n;
if(cin.fail() || n < 1 || n > 100) {
    cout << "Помилка введення кількості рядків!";
    return 1;
}

cout << "Введіть к-сть стовпців:";
cin >> m;
if(cin.fail() || m < 2 || m > n) {
    cout << "Помилка введення кількості стовпців!";
    return 1;
}

if(!matrix(a,n,m)){
    return 1;
}

int result = findMaxSum(a,n,m);
cout << "Максимальна сума: " << result << endl;

    return 0;
}
