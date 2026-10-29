#include <iostream>

using namespace std;

void sort(int a[], int N);

int main(){
    int N;
    cin >> N;

    int r[N];

    for(int i = 0; i < N; i++){
        cin >> r[i];
    }

    sort(r, N);

    if (N == 1){
        cout << 0;
    }else if(N == 2){
        cout << r[0];
    }else{
        int min1 = r[N-1] - r[1];
        int min2 = r[N-2] - r[0];
        int less = (min1 < min2) ? min1:min2;
        cout << less;
    }
}

void sort(int a[], int N){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N - 1 - i; j++){
            if (a[j+1]<a[j]) {
                int b = a[j];
                a[j] = a[j+1];
                a[j+1] = b;
            }
    }
    }
}