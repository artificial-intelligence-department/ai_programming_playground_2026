/* 
Задача: Лабораторна робота Algotester №4(2)
Варіант: №3
Автор: Вероніка Третяк
Група: ШІ-13
*/
#include <iostream>

using namespace std;

bool whatFirst(int a, int b){
    int ra = a % 3;
    int rb = b % 3;
    if(ra != rb){
        return ra < rb;
    }
    if(ra == 1){
        return a > b;
    }
    return a < b;
}
void mergeSort(int a[], int tmp[], int left, int right){
    if(left >= right){
        return;
    }
    int mid = (left + right) / 2;
    mergeSort(a, tmp, left, mid);
    mergeSort(a, tmp, mid + 1, right);

    int i = left;
    int j = mid + 1;
    int k = left;
    while(i <= mid && j <= right){
        if(whatFirst(a[j], a[i])){
            tmp[k] = a[j];
            j++;
        }
        else{
            tmp[k] = a[i];
            i++;
        }
        k++;
}
while(i <= mid){
    tmp[k] = a[i];
    i++;
    k++;
}
while(j <= right){
    tmp[k] = a[j];
    j++;
    k++;
}
for(int p = left; p <= right; p++){
    a[p] = tmp[p];
}

}

int main(){
    int n;
    cin >> n;
    int a[1000];
    int tmp[1000];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    mergeSort(a, tmp, 0, n - 1);
    int b = 1;
    for(int i = 1; i < n; i++){
        if(a[i] != a[b - 1]){
            a[b] = a[i];
            b++;
        }
    }
    cout << b << '\n';
    for(int i = 0; i < b; i++){
        if(i > 0){
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
    return 0;

}