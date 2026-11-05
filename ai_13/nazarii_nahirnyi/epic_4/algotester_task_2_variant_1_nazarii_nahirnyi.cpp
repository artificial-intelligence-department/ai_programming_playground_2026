/*
Algotster Lab 2v1, Нагірний Назарій, ШІ-13
*/
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int n=0;
    cin >> n;
    
int arr[n];
for (int i=0; i<n; i++){
    cin >> arr[i];
}
if (n <= 1) {
    cout << 0;
    return 0;
}
sort(arr, arr + n);

    int ans;
    if (arr[1]-arr[0]<arr[n-1]-arr[n-2]){
        ans=arr[n-2]-arr[0];
    }
    else ans=arr[n-1]-arr[1];
    cout << ans;
return 0;
}
