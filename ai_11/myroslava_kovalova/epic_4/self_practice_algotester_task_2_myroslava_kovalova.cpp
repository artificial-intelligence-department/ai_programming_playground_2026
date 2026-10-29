#include <iostream>
using namespace std;

int arr[1000000]={0};

int partition(int arr[], int start, int end){
    int index=start;
    int el_at=end;
    for (int j = start; j<end; j++){
        if (arr[j]<=arr[el_at]){
            int t = arr[index];
            arr[index]=arr[j];
            arr[j]=t;
            index++;            
        }
    }
    int t = arr[index];
    arr[index]=arr[el_at];
    arr[el_at]=t;
    return index;
}
void quickSort(int arr[], int start, int end){
    if(start>=end) return;
    int el_at = partition(arr, start, end);
    quickSort(arr,start, el_at-1);
    quickSort(arr, el_at+1, end);
}

int main(){
    short int n,m;
    cin>>n>>m;
    for (int i=0; i<n*m; i++){
        cin>>arr[i];        
    }
    int size= n*m;
    quickSort(arr,0, size-1);
    int k = 0;
    for (int i = 0; i<size-1; i++){
        if (arr[i]==arr[i+1]){
            k++;
        }
    }
    cout<<k<<endl;
    for (int i = 0; i<size-1; i++){
        if (arr[i]==arr[i+1]){
            cout<<arr[i]<<" ";
        }
    }
}