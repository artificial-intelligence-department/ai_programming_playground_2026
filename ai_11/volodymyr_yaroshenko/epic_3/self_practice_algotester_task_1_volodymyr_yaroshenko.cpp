/*  
Self Practice завдання 1
Ярошенко Володимир 
11 група 
*/
#include <iostream>
using namespace std;

long long sum(int l,int r, long long suma[]) {
    return suma[r] - suma[l - 1];
}

int main() {
int n;
int m;
cin >> n;
cin >> m;
int arr[100001] = {};
long long suma[100001] = {};

for(int i = 1;i<=n; i++) {
    cin >> arr[i];
    suma[i] = suma[i-1] + arr[i];
}
while(m !=0) {
    int choise;
 cin >> choise;
if(choise == 1) {
    int l, r;
    cin >> l >>r;
    cout << sum(l,r,suma) << endl;
}
else {
    int i,d;
    cin >> i >> d;
arr[i] +=d; 
for(int j = i; j <=n; j++) {
    suma[j] +=d;
}
}   
m--;
}
return 0;
}