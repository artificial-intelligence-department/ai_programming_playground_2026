#include <iostream>

using namespace std;

int main(){
    int N, K;
    cin >> N >> K;
    int *a = new int[N];
    for(int i=0;i<N;i++){
        cin >> a[i];
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N-1;j++){
            if(a[j]>a[j+1]){
                int t = a[j+1];
                a[j+1] = a[j];
                a[j] = t;
            }
        }
    }
    int n = 0, j=0;
    for(int i=0;i<N;i++){
        if(i == 0  || a[i] != a[i-1]){
            a[n++] = a[i];
        }
    }
    j=0;
    int k = K % n;
    int *r = new int[n];
    for(int i=n-k;i<n;i++){
        r[i] = a[j];
        j++;
    }
    for(int i=0;i<n-k;i++){
        r[i] = a[i+k];
    }
    delete[] a;
    a = r;
    cout << n << endl;
    for(int i=0;i<n;i++){
        cout << a[i] << " ";
    }
    delete[] r;
    return 0;
}