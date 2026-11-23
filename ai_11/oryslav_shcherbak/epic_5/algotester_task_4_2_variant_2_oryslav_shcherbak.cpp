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
    int m = 0;
    for(int i = 0; i < n; i++){
        bool repeat = false;
        for(int j = 0; j < m; j++){
            if(a[i] == a[j]){
                repeat = true;
                break;
            }
        }
        if(!repeat){
            a[m] = a[i];
            m++;
        }
    }
    k %=m;
    int* b = new int[m];
    int j = 0;
    for(int i = k; i < m; i++){
        b[j] = a[i];
        j++;
    }
    for(int i = 0; i < k; i++){
        b[j] = a[i];
        j++;
    }
    cout << m << endl;
    for(int i = 0; i < m; i++){
        cout << b[i] << " ";
    }
    delete[] a;
    delete[] b;
    return 0;
}