#include <iostream>
using namespace std;

int* arrayOfSums(const int* arr, int& n){
    if(n < 2){
        n = 0; 
        return nullptr;
    }
    n = n - 1;
    int *sum = new int[n];
    for(int i = 0; i < n; i++){
        sum[i] = arr[i] + arr[i+1];
    }
    return sum;
}

int main(){

    int n;
    cin >> n;
    int *arr = new int[n];
    int *temp = nullptr;    

    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    int a, b, c;
    cin >> a >> b >> c;

    int count = 0;
    for(int i = 0; i < n; i++){
        if(arr[i] == a || arr[i] == b || arr[i] == c){
            count ++;
        }
    }

    if(count > 0){
        temp = new int[n-count];
        int j = 0;
        for(int i = 0; i < n; i++){
            if(arr[i] != a && arr[i] != b && arr[i] != c){
                temp[j++] = arr[i]; 
            }
        }
        delete[] arr;
        arr = temp;
        temp = nullptr;
        n = j;

    }
    temp = arrayOfSums(arr, n);
    delete[] arr;
    arr = temp;
    temp = nullptr;

    cout << n << endl;
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    delete[] arr;
    arr = nullptr;

    return 0;
}