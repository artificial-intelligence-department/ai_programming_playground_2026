/*
    Задача: Перехід дороги
    Михайловська Анна
    ШІ-14
*/
#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;

    int a[100000];

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int count=0;

    for (int j = 0; j < n-1; j++) {
        if (a[j]%2==0 && a[j+1]%2==1)
        count +=1;

        if (a[j]%2==1 && a[j+1]%2==0)
        count +=1;
    }

    cout << count;    
    return 0;
}
    
    
