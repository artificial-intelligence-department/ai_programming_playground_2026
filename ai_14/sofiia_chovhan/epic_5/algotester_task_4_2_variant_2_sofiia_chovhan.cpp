/*Algotester task 4 1(without stl)
Sofiia Chovhan 
Variant 2*/
#include <iostream>
using namespace std;

int main(){
int K, N;
cin >> N;
cin >> K;
bool used[101] = {};
for(int i = 0; i < N; i++){
    int x;
    cin >> x;
    used[x] = true;

}
int a[101];
int M = 0;
for( int i =0; i < 101; i++){

if(used[i] == true){
    a[M] = i;
    M++;
}

}
int b[101];
for(int i = 0; i < M; i++){
    b[i] = a[(i + K) % M];
}
cout << M <<'\n';
for(int i = 0; i < M; i++){
    cout << b[i] << " ";
}
    return 0;
}