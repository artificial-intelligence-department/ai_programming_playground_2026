#include <iostream>

using namespace std;
int main(){
int n = 0;
cin >> n;
const int m = n;
int num [m];
for(int i = 0; i < m; i++){
    cin >> num[i];
}
int Max = num[0];
for(int i = 0; i < n; i++){
if (num[i] > Max){
    Max = num[i];
}
}
cout << Max;
}