// algotester lab 4 variant 2
// Челяда Андрій, ШІ-13

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int N, K;
    int arr[1000];

    cin >> N >> K;
    if (N < 1 || N > 1000 || K < 1 || K > 1000){
        return 0;
    }

    for (int i = 0; i < N; i++){
        cin >> arr[i];
    }

    sort(arr, arr + N);
    int newN = unique(arr, arr + N) - arr;
    int mv = 0;
    mv = K % newN;
    rotate(arr, arr + mv, arr + newN);


    cout << newN << endl;
    for (int i = 0; i < newN; i++){
        cout << arr[i] << " ";
    }   
    cout << endl;

    return 0;
}