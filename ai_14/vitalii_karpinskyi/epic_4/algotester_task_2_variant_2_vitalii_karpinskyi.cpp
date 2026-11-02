#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;
    int *arr = new int[N];
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    int a, b, c;
    cin >> a >> b >> c;

    int *arr_2 = new int[N];

    int N_2 = 0;
    for (int i = 0; i < N; i++) {
        if (arr[i] != a && arr[i] != b && arr[i] != c ) {
            arr_2[N_2] = arr[i];
            N_2++;
        }
    }
    delete[] arr;
    arr = nullptr;

    if (N_2 < 2) {
        cout << 0;
        delete[] arr_2;
        arr_2 = nullptr;
        return 0;
    }

    for (int i = 0; i < N_2 - 1; i++) {
        arr_2[i] = arr_2[i] + arr_2[i + 1];
    }
    cout << N_2 - 1 << endl;
    for (int i = 0; i < N_2 - 1; i++) {
        cout << arr_2[i] << " ";
    }
    delete[] arr_2;
    arr_2 = nullptr;

    return 0;
}