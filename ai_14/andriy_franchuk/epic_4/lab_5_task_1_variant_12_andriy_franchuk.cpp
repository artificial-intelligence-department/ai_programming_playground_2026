#include <iostream>

using namespace std;

const int max_size = 100;

int max(const int a[][max_size], int m, int n);
void print(const int a[][max_size], int m, int n);

int main(){
    int m, n;
    cin >> m >> n;

    int a[max_size][max_size];

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cin >> a[i][j];
        }
    }
    print(a, m, n);

    int b[max_size][max_size];
    int max1;

    for(int i = 0; i < m; i++){
        max1 = max(a, i + 1, n);
        for(int j = 0; j < n; j++){
            b[i][j] = a[i][(j + max1)%n];
        }
    }

    print(b, m, n);
}

int max(const int a[][max_size], int m, int n){
    int max;
    max = a[m-1][0];
    for(int j = 1; j < n; j++){
        if(a[m-1][j] > max){
            max = a[m-1][j];
        }
    }
    return max;
}

void print(const int a[][max_size], int m, int n){
    cout << " " << endl;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}