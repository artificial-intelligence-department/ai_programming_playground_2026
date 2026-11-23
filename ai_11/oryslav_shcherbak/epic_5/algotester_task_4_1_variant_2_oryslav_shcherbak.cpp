#include <iostream>
#include <algorithm>
using namespace std;

/*
 * Задача: Algotester Lab4v2
 * Щербак Орислав
 * Група ШІ-11
 */

int main(){
    int n, k;
    cin >> n >> k;
    int* a = new int[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }   
    sort(a, a+n);
    int* last = unique(a, a + n);
    int m = last - a;
    k %= m;
    rotate(a, a+k, a+m);
    cout << m << endl;
    for(int i = 0; i < m; i++){
        cout << a[i] << " ";
    }
    delete[] a;
    return 0;
}