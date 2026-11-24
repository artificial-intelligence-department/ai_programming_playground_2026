/*Algotester task 4 1(with stl)
Sofiia Chovhan 
Variant 2*/
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;
int main(){
int K, N;
cin >> N >> K;
set<int> numbers;
for(int i = 0; i < N; i++){
int x;
cin >> x;
numbers.insert(x);
}
int a[101];
int M = 0;
for(int x: numbers){
a[M] = x;
M++;
}
rotate(a, a + K % M,a + M);
cout << M << endl;
for(int i = 0; i < M; i++){
cout << a[i] << " ";
}

    return 0;
}