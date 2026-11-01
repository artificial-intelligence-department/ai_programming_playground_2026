/* 
Автор: Давидович Святослав
Група: ШІ-11
Умова: https://algotester.com/uk/ArchiveProblem/DisplayWithEditor/40598
*/
#include <iostream>
#include <cmath>

using namespace std;
using ll = long long;

ll* merge(ll arr1[], int len1, ll arr2[], int len2){
    ll *p = new ll[len1+len2];

    int left = 0, right = 0, current = 0;
    while (left < len1 && right < len2){
        if (arr1[left]<=arr2[right]){
            p[current]=arr1[left];
            current++;
            left++;
        } 
        else {
            p[current]=arr2[right];
            current++;
            right++;
        }
    }

    while (left<len1){
        p[current]=arr1[left];
        current++;
        left++;
    }
    while(right<len2){
        p[current]=arr2[right];
        current++;
        right++;
    }

    return p;
}

void mergeSort(ll arr[], int n){
    if (n<=1) return;
    
    int l = 0, r = n-1;
    int m = (l+r)/2;

    int size1 = m-l+1;
    int size2 = r-m; 
    ll arr1[size1], arr2[size2];
    for (int i = 0; i<size1; i++){
        arr1[i]=arr[l+i];
    }
    for (int i = 0; i<size2; i++){
        arr2[i]=arr[m+i+1];
    }

    mergeSort(arr1, size1);
    mergeSort(arr2, size2);

    ll *merged = merge(arr1, size1, arr2, size2);
    for (int i = 0; i<n; i++){
        arr[i]=merged[i];
    }
    delete[] merged;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    ll x;
    cin >> n >> m >> x;

    ll arr1[n], arr2[m];

    for (int i = 0; i<n; i++){
        cin >> arr1[i];
    }
    for (int i = 0; i<m; i++){
        cin >> arr2[i];
    }
    
    mergeSort(arr1, n);
    mergeSort(arr2, m);

    int left = 0; 
    int right = m-1; 

    ll sum = arr1[left]+arr2[right];
    ll min = abs(sum-x);
    while(left<n && right>=0){
        sum = arr1[left]+arr2[right];
        if (abs(sum-x)<min) min = abs(sum-x);

        if (sum<=x) left++;
        else right--;
    }

    cout << min; 
}   