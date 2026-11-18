/*  
Algotester 4
Варіант 3(STL) 
Ярошенко Володимир 
11 група 
*/
#include <iostream>
#include <algorithm>
using namespace std;
int main(){
int n =0;
cin >> n;
int* a = new int[n]; 
for(int i =0; i<n; i++){
cin >> a[i];
}
int* p1 = partition(a, a+n, [](int x){
    return x % 3 == 0;
});
int* p2 = partition(p1, a+n, [](int x){
    return x % 3 == 1;
});
sort(a ,p1);
sort(p2, a+n);
sort(p1, p2, [](int x ,int y) {
return x>y;
});
int* b = unique(a, a + n);
cout << b-a << endl;
for(int i =0; i<b-a; i++){
    cout << a[i] << ' ';
}
    return 0;
}
