#include <iostream>
#include <algorithm>
using namespace std;

void dif1(int n[], int N, int m[], int M) {
    bool used[100] = {};
    int result[100];
    int count = 0;
    for (int i = 0; i < N; i++) {
        bool found = false;
        for (int j = 0; j < M; j++) {
            if (n[i] == m[j] && !used[j]) {
                used[j] = true;
                found = true;
                break;
            }
        }
        if (!found) {
            result[count++] = n[i];
        }
    }
    cout << count << endl;
    for (int i = 0; i < count; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}

void dif2(int n[], int N, int m[], int M) {
    bool used[100] = {};
    int result[100];
    int count = 0;
    for (int i = 0; i < M; i++) {
        bool found = false;
        for (int j = 0; j < N; j++) {
            if (m[i] == n[j] && !used[j]) {
                used[j] = true;
                found = true;
                break;
            }
        }
        if (!found) {
            result[count++] = m[i];
        }
    }
    cout << count << endl;
    for (int i = 0; i < count; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}

void intersection(int n[], int N, int m[], int M) {
    bool used[100] = {};
    int result[100];
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (n[i] == m[j] && !used[j]) {
                result[count++] = n[i];
                used[j] = true;
                break;
            }
        }
    }
    cout << count << endl;
    for (int i = 0; i < count; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}

void all(int n[], int N, int m[], int M) {
    bool used[100] = {};
    int result[200];
    int count = 0;
    for (int i = 0; i < N; i++) {
        result[count++] = n[i];
    }
    for (int i = 0; i < M; i++) {
        bool found = false;
        for (int j = 0; j < N; j++) {
            if (m[i] == n[j] && !used[j]) {
                used[j] = true;
                found = true;
                break;
            }
        }
        if (!found) {
            result[count++] = m[i];
        }
    }
    sort(result, result + count);
    cout << count << endl;
    for (int i = 0; i < count; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}

void symDif(int n[], int N, int m[], int M) {
    bool used[100] = {};
    int result[200];
    int count = 0;
    for (int i = 0; i < N; i++) {
        bool found = false;
        for (int j = 0; j < M; j++) {
            if (n[i] == m[j] && !used[j]) {
                used[j] = true;
                found = true;
                break;
            }
        }
        if (!found) {
            result[count++] = n[i];
        }
    }
    for (int i = 0; i < M; i++) {
        if (!used[i]) {
            result[count++] = m[i];
        }
    }
    sort(result, result + count);
    cout << count << endl;
    for (int i = 0; i < count; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}

int main() {
    int N, M;
    int n[100], m[100];
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> n[i];
    }
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> m[i];
    }
    sort(n, n + N);
    sort(m, m + M);
    dif1(n, N, m, M);
    dif2(n, N, m, M);
    intersection(n, N, m, M);
    all(n, N, m, M);
    symDif(n, N, m, M);
    return 0;
}