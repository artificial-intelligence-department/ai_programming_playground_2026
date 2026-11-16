/*Algotester Task 4 Variant 1 without STL
Автор:Сенько Вікторія
Група: ШІ-12 group3*/
#include <iostream>
using namespace std;

const int Max = 100;

void InsertionSort(int arr[], int size){
    for(int i=1; i<size; i++){
        int key=arr[i];
        int j=i - 1;
        while(j>=0 && arr[j]>key){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}
int Difference(int a[], int n, int b[], int m, int result[]){
    int i=0, j=0, size=0;
    while(i<n){
        if(j>=m || a[i]<b[j]){
            result[size++]=a[i++];
        } else if(a[i]==b[j]){
            i++;
            j++;
        } else j++;
    }
    return size;
}

int Intersection(int a[], int n, int b[], int m, int result[]){
    int i=0, j=0, size=0;
    while(i<n && j<m){
        if(a[i]<b[j])i++;
        else if(a[i] > b[j])j++;
        else {
            result[size++] = a[i];
            i++;
            j++;
        }
    }
    return size;
}

int Union(int a[], int n, int b[], int m, int result[]){
    int i=0, j = 0, size=0;
    while(i<n || j<m){
        if(j>=m || (i<n && a[i]<b[j])){
            result[size++] = a[i++];
        } else if(i >= n || b[j] < a[i]){
            result[size++] = b[j++];
        } else {
            result[size++] = a[i];
            i++;
            j++;
        }
    }
    return size;
}

int SymmetricDifference(int a[], int n, int b[], int m, int result[]){
    int i=0, j=0, size=0;
    while(i<n || j<m){
        if(j>=m || (i < n && a[i] < b[j])){
            result[size++] = a[i++];
        } else if(i >= n || b[j] < a[i]){
            result[size++] = b[j++];
        } else {
            i++;
            j++;
        }
    }
    return size;
}

void PrintSet(int result[], int size){
    cout<<size<<endl;
    for(int i=0; i<size; i++){
        if(i>0) cout << " ";
        cout<< result[i];
    }
    cout<<endl;
}

int main() {
    int n[Max];
    int m[Max];
    int result[2 * Max];
    int N, M, size;

    cin>>N;
    for(int i=0; i<N; i++){
        cin>> n[i];
    }
    cin>>M;
    for(int i=0; i<M; i++){
        cin>> m[i];
    }

    InsertionSort(n, N);
    InsertionSort(m, M);

    size=Difference(n, N, m, M, result);
    PrintSet(result, size);
    cout << endl;

    size=Difference(m, M, n, N, result);
    PrintSet(result, size);
    cout << endl;

    size=Intersection(n, N, m, M, result);
    PrintSet(result, size);
    cout << endl;

    size=Union(n, N, m, M, result);
    PrintSet(result, size);
    cout << endl;

    size=SymmetricDifference(n, N, m, M, result);
    PrintSet(result, size);

    return 0;
}