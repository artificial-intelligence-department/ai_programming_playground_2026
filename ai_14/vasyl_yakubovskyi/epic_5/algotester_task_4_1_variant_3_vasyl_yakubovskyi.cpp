/*
Task 3 lab 4v3(STL)
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/


#include <iostream>
#include <algorithm>

using namespace std;

const int MAXSIZE = 1000;

int main ( ){
    int n = 0;
    cin >> n;

    int a[MAXSIZE];

    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    int *p1 = partition(a, a + n, [](int x){return x % 3 == 0;});
    int *p2 = partition(p1, a + n, [](int x){return x % 3 == 1;});

    sort(a, p1);

    sort(p1, p2, [](int a, int b){return a > b;});

    sort(p2, a + n);

    int *new_a = unique(a, a + n);
    int new_n = new_a - a;

    cout << new_n << endl;

    for (int i = 0 ; i < new_n; i++){
        cout << a[i] << " ";

    }
    cout << endl;


    return 0;
}