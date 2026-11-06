#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long n,m,x;
    long long res = __LONG_LONG_MAX__;
    cin >> n >> m >> x;

    long long *mas1 = new long long[n];
    long long *mas2 = new long long[m];

    for(long long i = 0; i < n; i++){
        cin >> mas1[i];
    }
    for(long long i = 0; i < m; i++){
        cin >> mas2[i];
    }
    sort(mas1, mas1+n);
    sort(mas2, mas2+m);

    long long i = 0;
    long long j = m - 1;
    while(i < n && j >= 0){
        long long sum = mas1[i] + mas2[j];
        if(abs(sum - x) < res){
            res = abs(sum - x);
        }
        if(res == 0){break;}
        if(sum < x){i++;}
        else{j--;}
    }

    cout << res;

    delete[] mas1;
    mas1 = nullptr;
    delete[] mas2;
    mas2 = nullptr;
    return 0;
}