#include <iostream>
using namespace std;
bool contains(int a[], int s, int b){//функція на перевірку унікальності елемента
    for(int i = 0; i<s; i++){
        if(a[i] == b)return true;
    }return false;
}
void mergeSort(int *a, int *temp, int start, int end){
    if(start >= end) return;//умова виходу з рекурсії
    int mid = start + (end - start) / 2;
    mergeSort(a, temp, start, mid);//рекурсивне сортування лівої і правої половини
    mergeSort(a, temp, mid+1, end);
    int i = start, j = mid+1, k = start;
    while (i <= mid && j <= end){
        if(a[i] <= a[j]){//порівнювання поточних найменших елементів
            temp[k++] = a[i++];
        }else{//запис залежно від результату і зсув вказівників
            temp[k++] = a[j++];
        }
    }
    while(i <= mid)temp[k++] = a[i++];//дописування тої половини яку ще не вичерпали
    while(j <= end)temp[k++] = a[j++];

    for(int m = start; m <= end; m++){
        a[m] = temp[m];//перепризначення тимчасових елементів у сам масив
    }
}
int main(){
    int N;
    int len0 = 0, len1 = 0, len2 = 0;
    cin >> N;
    int Nnew = N;
    int *arr = new int[N] {0};
    int *temp = new int[N];
    int *ost0 = new int[N];//5 динамічних масивів...
    int *ost1 = new int[N];
    int *ost2 = new int[N];
    for(int i = 0; i<N; i++){
        cin >> arr[i];
            if(!contains(arr, i, arr[i])){//перевірка на унікальність
            switch(arr[i] % 3){//розподілення у три різні групи по остачі від 3
                case 0:
                    ost0[len0++] = arr[i];
                    break;
                case 1:
                    ost1[len1++] = arr[i];
                    break;
                case 2:
                    ost2[len2++] = arr[i];
                    break;
            }
        } else Nnew--;
    }
    mergeSort(ost0, temp, 0, len0 - 1);
    mergeSort(ost1, temp, 0, len1 - 1);//сортування по зростанню
    mergeSort(ost2, temp, 0, len2 - 1);
    cout << Nnew <<endl;
    for(int i = 0; i<len0; i++){
        cout << ost0[i] << " ";
    }
    for(int i = len1 - 1; i>=0; i--){//вивід по спаданню
        cout << ost1[i] << " ";
    }
    for(int i = 0; i<len2; i++){
        cout << ost2[i] << " ";
    }
    delete[] arr;
    delete[] temp;
    delete[] ost0;
    delete[] ost1;
    delete[] ost2;
}