#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int a[1000];
    for (int i = 0; i<n; i++){
        cin >> a[i];
    }
    int a0[1000], a1[1000], a2[1000];
    int n0 = 0, n1 = 0, n2 = 0;
    for (int i = 0; i < n; i++) {
    if (a[i] % 3 == 0) {
        a0[n0] = a[i];
        n0++;
    }
    else if (a[i] % 3 == 1) {
        a1[n1] = a[i];
        n1++;
    }
    else {
        a2[n2] = a[i];
        n2++;
    }
}
for (int i = 0; i < n0 - 1; i++) {
    int min = i;
    for (int j = i + 1; j < n0; j++) {
        if (a0[j]< a0[min]){
            min=j;
        }
    }
int temp = a0[i];
a0[i] = a0[min];
a0[min] = temp;
}
for (int i = 0; i < n1 - 1; i++) {
    int max = i;
    for (int j = i + 1; j < n1; j++) {
        if (a1[j]>a1[max]){
            max=j;
        }
}
int temp = a1[i];
a1[i] = a1[max];
a1[max] = temp;
}
for (int i = 0; i < n2 - 1; i++) {
    int min = i;
    for (int j = i + 1; j < n2; j++) {
        if (a2[j]<a2[min]){
            min=j;
        }
}
int temp = a2[i];
a2[i] = a2[min];
a2[min] = temp;
}
int result[1000];
int m = 0;
for (int i = 0; i < n0; i++) {
    if (m == 0 || result[m - 1] != a0[i]){
       result[m] = a0[i];
       m++; 
    }
}
for (int i = 0; i < n1; i++) {
    if (m == 0 || result[m - 1] != a1[i]){
       result[m] = a1[i];
       m++; 
    }
}
for (int i = 0; i < n2; i++) {
    if (m == 0 || result[m - 1] != a2[i]){
       result[m] = a2[i];
       m++; 
    }
}
cout<<m<<endl;
for (int i = 0; i<m; i++){
    cout << result[i] << " ";
}
    return 0;
}
