
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int N;
    cin >> N;

    int *N_arr = new int[N];

    for (int i = 0; i < N; i++) {
        cin >> N_arr[i];
    }

    int M;
    cin >> M;

    int *M_arr = new int[M];

    for (int i = 0; i < M; i++) {
        cin >> M_arr[i];
    }

    sort(N_arr, N_arr + N);
    sort(M_arr, M_arr + M);

    bool isUnique = true;
    int count = 0;
    int countN, countM;

    int *result = new int[N + M];

    // Block 1: N - M

    count = 0;

    for (int i = 0; i < N; i++) {
        countN = 0;
        countM = 0;

        for (int j = 0; j <= i; j++) {
            if (N_arr[i] == N_arr[j]) {
                countN++;
            }
        }

        for (int j = 0; j < M; j++) {
            if (N_arr[i] == M_arr[j]) {
                countM++;
            }
        }

        if (countN > countM) {
            count++;
        }
    }

    cout << count << endl;

    for (int i = 0; i < N; i++) {
        countN = 0;
        countM = 0;

        for (int j = 0; j <= i; j++) {
            if (N_arr[i] == N_arr[j]) {
                countN++;
            }
        }

        for (int j = 0; j < M; j++) {
            if (N_arr[i] == M_arr[j]) {
                countM++;
            }
        }

        if (countN > countM) {
            cout << N_arr[i] << " ";
        }
    }

    cout << endl;

    // Block 2: M - N

    count = 0;

    for (int i = 0; i < M; i++) {
        countM = 0;
        countN = 0;

        for (int j = 0; j <= i; j++) {
            if (M_arr[i] == M_arr[j]) {
                countM++;
            }
        }

        for (int j = 0; j < N; j++) {
            if (M_arr[i] == N_arr[j]) {
                countN++;
            }
        }

        if (countM > countN) {
            count++;
        }
    }

    cout << count << endl;

    for (int i = 0; i < M; i++) {
        countM = 0;
        countN = 0;

        for (int j = 0; j <= i; j++) {
            if (M_arr[i] == M_arr[j]) {
                countM++;
            }
        }

        for (int j = 0; j < N; j++) {
            if (M_arr[i] == N_arr[j]) {
                countN++;
            }
        }

        if (countM > countN) {
            cout << M_arr[i] << " ";
        }
    }

    cout << endl;

    // Block 3: Intersection

    count = 0;

    for (int i = 0; i < N; i++) {
        countN = 0;
        countM = 0;

        for (int j = 0; j <= i; j++) {
            if (N_arr[i] == N_arr[j]) {
                countN++;
            }
        }

        for (int j = 0; j < M; j++) {
            if (N_arr[i] == M_arr[j]) {
                countM++;
            }
        }

        if (countN <= countM) {
            count++;
        }
    }

    cout << count << endl;

    for (int i = 0; i < N; i++) {
        countN = 0;
        countM = 0;

        for (int j = 0; j <= i; j++) {
            if (N_arr[i] == N_arr[j]) {
                countN++;
            }
        }

        for (int j = 0; j < M; j++) {
            if (N_arr[i] == M_arr[j]) {
                countM++;
            }
        }

        if (countN <= countM) {
            cout << N_arr[i] << " ";
        }
    }

    cout << endl;

    // Block 4: Union

    count = N;

    for (int i = 0; i < M; i++) {
        countM = 0;
        countN = 0;

        for (int j = 0; j <= i; j++) {
            if (M_arr[i] == M_arr[j]) {
                countM++;
            }
        }

        for (int j = 0; j < N; j++) {
            if (M_arr[i] == N_arr[j]) {
                countN++;
            }
        }

        if (countM > countN) {
            count++;
        }
    }

    int k = 0;

    for (int i = 0; i < N; i++) {
        result[k++] = N_arr[i];
    }

    for (int i = 0; i < M; i++) {
        countM = 0;
        countN = 0;

        for (int j = 0; j <= i; j++) {
            if (M_arr[i] == M_arr[j]) {
                countM++;
            }
        }

        for (int j = 0; j < N; j++) {
            if (M_arr[i] == N_arr[j]) {
                countN++;
            }
        }

        if (countM > countN) {
            result[k++] = M_arr[i];
        }
    }

    sort(result, result + k);

    cout << k << endl;

    for (int i = 0; i < k; i++) {
        cout << result[i] << " ";
    }

    cout << endl;

    // Block 5: Symmetric difference

    count = 0;

    for (int i = 0; i < N; i++) {
        countN = 0;
        countM = 0;

        for (int j = 0; j <= i; j++) {
            if (N_arr[i] == N_arr[j]) {
                countN++;
            }
        }

        for (int j = 0; j < M; j++) {
            if (N_arr[i] == M_arr[j]) {
                countM++;
            }
        }

        if (countN > countM) {
            count++;
        }
    }

    for (int i = 0; i < M; i++) {
        countM = 0;
        countN = 0;

        for (int j = 0; j <= i; j++) {
            if (M_arr[i] == M_arr[j]) {
                countM++;
            }
        }

        for (int j = 0; j < N; j++) {
            if (M_arr[i] == N_arr[j]) {
                countN++;
            }
        }

        if (countM > countN) {
            count++;
        }
    }

    k = 0;

    for (int i = 0; i < N; i++) {
        countN = 0;
        countM = 0;

        for (int j = 0; j <= i; j++) {
            if (N_arr[i] == N_arr[j]) {
                countN++;
            }
        }

        for (int j = 0; j < M; j++) {
            if (N_arr[i] == M_arr[j]) {
                countM++;
            }
        }

        if (countN > countM) {
            result[k++] = N_arr[i];
        }
    }

    for (int i = 0; i < M; i++) {
        countM = 0;
        countN = 0;

        for (int j = 0; j <= i; j++) {
            if (M_arr[i] == M_arr[j]) {
                countM++;
            }
        }

        for (int j = 0; j < N; j++) {
            if (M_arr[i] == N_arr[j]) {
                countN++;
            }
        }

        if (countM > countN) {
            result[k++] = M_arr[i];
        }
    }

    sort(result, result + k);

    cout << k << endl;

    for (int i = 0; i < k; i++) {
        cout << result[i] << " ";
    }

    cout << endl;

    delete[] result;
    delete[] N_arr;
    delete[] M_arr;

    return 0;
}
