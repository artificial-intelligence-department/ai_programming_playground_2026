#include <iostream>

using namespace std;

int main() {
    int N = 0;
    cin >> N;
    int *a = new int[N];
    for (int i = 0; i < N; i++) {
        cin >> *(a + i);
    }
    int M = 0;
    cin >> M;
    int *b = new int[M];
    for (int i = 0; i < M; i++) {
        cin >> *(b + i);
    }
    int count1 = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (a[i] == b[j]) {
                count1++;
            }
        }
    }
    int count2 = N + M - count1;
    cout << count1 << endl;
    cout << count2 << endl;

    delete[] a;
    a = nullptr;
    delete[] b;
    b = nullptr;
    
    return 0;
}