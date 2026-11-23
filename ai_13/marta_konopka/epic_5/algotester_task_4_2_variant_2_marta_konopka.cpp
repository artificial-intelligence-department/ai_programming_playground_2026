#include<iostream>
using namespace std;

void merge(int a[], int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[1000], R[1000];
    for(int i = 0; i < n1; i++){
        L[i] = a[left + i];
    }
    for(int j = 0; j < n2; j++){
        R[j] = a[mid + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = left;
    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            a[k] = L[i];
            i++;
        }
        else if(L[i] > R[j]){
            a[k] = R[j];
            j++;
        }
        else{
            a[k] = R[j];
            j++;
        }
        k++;
    }
    while(i < n1){
        a[k] = L[i];
        i++;
        k++;
    }
    while(j < n2){
        a[k]= R[j];
        j++;
        k++;
    }
}
void mergeSort(int a[], int left, int right){
    if(left >= right){
        return;
    }
    int mid = (left + right) / 2;
    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);
    merge(a, left, mid, right);
}

int main(){
    int n, k;
    cin >> n >> k;
    int a[1000];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    mergeSort(a, 0, n - 1);

    int unique[1000];
    int m = 0;
    for(int i = 0; i < n; i++){
        if(i == 0 || a[i] != a[i - 1]){
            unique[m] = a[i];
            m++;
        }
    }
    cout << m << endl;
    k %= m;
    for(int i = k; i < m; i++){
        cout << unique[i] << " ";
    }
    for(int i = 0; i < k; i++){
        cout << unique[i] << " ";
    }
    return 0;
}