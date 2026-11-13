#include <iostream>
using namespace std;

long long partition(long long arr[],long long low,long long high){
    long long pivot = arr[high];
    long long i = (low - 1);
    for (long long j = low; j < high; j++) {
        if(arr[j] < pivot){
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[high]);
    return (i + 1);
}
void QuickSort(long long arr[],long long low,long long high){
    if(low<high){
        long long pi = partition(arr,low,high);
        QuickSort(arr,low,pi-1);
        QuickSort(arr,pi+1,high);
    }
}


int main()
{
    long long n,k;
    cin >> n >> k;

    long long *a = new long long[n]();
    for (long long i = 0; i < n; i++) {
        cin >> a[i];
    }
    QuickSort(a,0,n-1);
    long long counter = 0;
    long long index = 0;
    long long *sorted_array = new long long[n]();
    for (long long i = 0; i < n; i++) {
        if(i == n - 1 ||a[i] != a[i+1]){
            counter++;
            sorted_array[index] = a[i];
            index++;
        }
    }
    cout << counter << endl;
    long long target_index = k;
    while (target_index >= counter) {
        target_index -= counter;
    }
    for (long long i = 0; i < counter; i++) {
        cout << sorted_array[target_index] << " ";
        target_index++;
        if(target_index >=counter){
            target_index=0;
        }
    }

    delete[] a;
    delete[] sorted_array;
    
    return 0;
}
