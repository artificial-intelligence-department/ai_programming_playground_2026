#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;

int main(){

    int n,m;
    long long x;
    cin >> n >> m >> x; // Де n,m розміри матриць , а х - бажане число

    long long answer = LLONG_MAX;
    long long t;
    long long d;

    long long* a = new long long[n];
    long long* b = new long long[m];

    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    for (int i = 0; i < m; i++){
        cin >> b[i];
    }

    // Перевірка, кожен і елемент в суммі з й елементом відняти х має по модулю бути меншим за модулі інших
    // for (int i = 0; i < n; i++){                 БО ДАЄ ПОМИЛКУ ПО ЧАСУ
    //     for (int j = 0; j < m; j++){
    //         t = a[i] + b[j];
    //         d = fabs(t - x);
    //         if (d < answer){
    //             answer = d;
    //         }
    //     }
    // }

    sort(a , a+n);
    sort(b , b+m);

    int i = 0;
    int j = m - 1;
    
    while ( i < n && j >= 0){
        t = a[i] + b[j];
        d = fabs(t - x);

        if ( d < answer ){
            answer = d;
        }

        if ( t < x ){
            i++;
        }
        else if ( t > x){
            j--;
        }
        else {
            break;
        }
        
    }

    cout << answer;

    delete[] a;
    delete[] b;

return 0;
}
