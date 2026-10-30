/*
    Algotester lab 2
    Михайловська Анна
    ШІ-14
    Варіант 2
*/

#include <iostream>
using namespace std;

int main(){
    int n, a, b, c, r[100000], d[100000];

    cin >> n;

    for(int i = 0; i < n; i++)
        cin >> r[i];

    cin >> a >> b >> c;

    int k = 0;
    for (int i = 0; i < n; i++) {
        if (r[i] != a && r[i] != b && r[i] != c) {
            r[k] = r[i]; 
            k++;
        }
    }

    for(int i = 0; i < k - 1; i++)
        d[i] = r[i] + r[i+1];

    if (k==0){
         cout << 0 << endl;
    }
    else {
        cout << k - 1 << endl;

        for(int i = 0; i < k - 1; i++)
            cout << d[i] << " ";
    }

    return 0;
}
