/*Епік 4. Лабораторна робота 4. Варіант 25
Автор: Матішак Михайло
Група: ШІ-11*/
#include <iostream>

using namespace std;

int main(){
    int N, K;
    int arr[100];

    cin >> N;
    if(N < 1 || N > 100){
        return 0;
    }
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
    cin >> K;
    if(K < 1 || K > N){
        return 0;
    }
    int j = K - 1;

    for(int i = 0; i < N; i++){
        cout << arr[j] << " ";
        j--;
        if(j < 0){
            j = N - 1;
        }
    }
    cout << endl;

    for(int i = 0; i < N - 1; i++){
        for(int j = 0; j < N - i - 1; j++){
            if(arr[j] < arr[j + 1]){
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    for(int i = 0; i < N; i++){
        if(arr[i] % 2 != 0){
            for(int j = i; j < N - 1; j++){
                arr[j] = arr[j + 1];
            }
            N--;
            i--;
        }
    }

    if(N == 0){
        cout << "Масив порожній";
        return 0;
    }

    j = (K - 1) % N;

    for(int i = 0; i < N; i++){
        cout << arr[j] << " ";
        j--;
        if(j < 0){
            j = N - 1;
        }
    }

    return 0;
}
