#include <iostream>

using namespace std;

void change(int **arr, int k, int r){
    int *arrT = arr[k];
    arr[k] = arr[r];
    arr[r] = arrT;
}

int main(){
    int n = 0;
    int m = 0;
    cout << "Введіть кількість рядків:";
    cin >> n;
    cout << "Введіть кількість елементів в рядках:";
    cin >> m;
    int **arr = new int *[n];
    for(int i = 0; i < n; i++){
        arr[i] = new int[m];
    }
    for(int g = 0; g < n; g++){
        for(int h = 0; h < m; h++){
            cin >> arr [g][h];
    }
}
if(m >= 3){
for(int k = 0; k < n - 1; k++){
    for(int r = 0; r < n - k - 1; r++){
        if(arr[r][2] > arr[r+ 1][2]){
            change(arr, r, r + 1);
        }
    }
}
}
    for(int g = 0; g < n; g++){
        for(int h = 0; h < m; h++){
            cout << arr [g][h] << " ";
    }
    cout << endl;
}
for(int x = 0; x < n; x++){
    delete[] arr[x];
}
delete[] arr;
arr = nullptr;
return 0;
}