#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void print(int* arr, int N){
    for (int i = 0; i < N; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";
}

void destroyElement(int* arr, int& N, int K){
    for (int i = K; i < N - 1; i++){
        arr[i] = arr[i + 1];
    }
    N--;
}

void addZeroEven(int* arr, int& N){
    for (int i = 0; i < N; i++){
        if (arr[i] % 2 == 0){
            for (int j = N; j > i + 1; j--){
                arr[j] = arr[j - 1];
            }
            N++;
            arr[i + 1] = 0;
            i++;
        }
    }
}

int main(){
    srand(time(nullptr));
    int N, K;
    cout << "Введіть N: ";
    cin >> N;
    cout << "Введіть K: ";
    cin >> K;
    int* arr = new int[N];
    for (int i = 0; i < N; i++){
        arr[i] = rand() % 100 + 1;
    }

    print(arr, N);
    destroyElement(arr, N, K);
    print(arr, N);
    addZeroEven(arr, N);
    print(arr, N);

    delete[] arr;
}