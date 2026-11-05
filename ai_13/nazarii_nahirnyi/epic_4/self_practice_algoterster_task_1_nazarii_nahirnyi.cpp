/*
Завдання: Офісна Вулиця. Частина 2
*/
#include <iostream>
#include <algorithm>
using namespace std;
int main(){
int n;
cin >> n;
int *l = new int[n];
for (int i = 0; i < n; i++){
    cin >> l[i]; 
}
int *w = new int[n];
for (int i = 0; i < n; i++){
    cin >> w[i];
}
pair<double, int> *a = new pair<double, int>[n];

    for (int i = 0; i < n; i++) {
        a[i].first = (double)l[i] / w[i];
        a[i].second = i + 1;
    }

    sort(a, a + n);

    for (int i = 0; i < n; i++) {
        cout << a[i].second << " ";
    }
     
    delete[] l;
    delete[] w;
    delete[] a;
    
    
return 0;
}