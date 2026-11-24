//Тренер слонів 0114
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long x [n];
    for (int i=0; i < n;i++) {
        cin >> x[i];
    }
    int minKr, maxKr;
    minKr=x[0];
    maxKr=x[0];
    for (int i=0;i<n;i++){
        if(x [i]<minKr) minKr = x[i];
        if(x [i]>maxKr) maxKr = x[i];
    }
    cout << maxKr - minKr;
}