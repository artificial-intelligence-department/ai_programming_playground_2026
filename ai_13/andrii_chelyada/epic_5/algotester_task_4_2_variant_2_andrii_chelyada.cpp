// algotester lab 4 variant 2
// Челяда Андрій, ШІ-13

#include <iostream>

using namespace std;

int main(){
    int N, K;
    int arr[1000];
    int res[1000];

    cin >> N >> K;
    if (N < 1 || N > 1000 || K < 1 || K > 1000){
        return 0;
    }

    for (int i = 0; i < N; i++){
        cin >> arr[i];
    }

    for(int i = 0; i < N - 1; i++){
        for(int j = 0; j < N - i - 1; j++){
            if(arr[j] > arr[j + 1]){
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    int newN = 1;
    for(int i = 1; i < N; i++){
        if(arr[i] != arr[newN - 1]){
            arr[newN] = arr[i];
            newN++;
        }
    }

    int mv = 0;
    mv = K % newN;

    for(int j = 0; j < newN; j++){
        res[j] = arr[(j + mv) % newN];
    }

    cout << newN << endl;
    for (int i = 0; i < newN; i++){
        cout << res[i] << " ";
    }

    cout << endl;

    return 0;
}