
/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <iostream>
using namespace std;

int main() {

    int N;
    cin >> N;
    int* arr1 = new int[N];
    for (int i = 0; i < N; i++) {
        cin >> arr1[i];
    }

    int M;
    cin >> M;
    int* arr2 = new int[M];
    for (int i = 0; i < M; i++) {
        cin >> arr2[i];
    }

    int common = 0;

    for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
        if (arr1[i] == arr2[j]) {
            common++;
            break;
        }
    }
    }

    cout << common << endl;
    cout << N + M - common << endl;

    delete[] arr1;
    delete[] arr2;

    return 0;
}