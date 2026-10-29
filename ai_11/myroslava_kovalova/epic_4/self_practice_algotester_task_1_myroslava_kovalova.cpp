#include <iostream>
using namespace std;

int partion( int arr[],int start, int end){
    int index = start;
    int el_at = end;
    for (int j = start; j<end+1; j++){
        if(arr[j]<=arr[el_at]){
            int t = arr[index];
            arr[index]=arr[j];
            arr[j]=t;
            index++;
        }
    }
    return index-1;

}
void quickSort(int arr[],int start, int end){
    if(start>=end) return;
    int el_at = partion(arr,start,end);
    quickSort(arr, start, el_at-1);
    quickSort(arr, el_at+1, end);
}

int main(){
    int arr[10000]={0};
    int t =0;
    int i = 0;
    while (cin>>t){
        arr[i]=t;
        i++;
    }
    
    quickSort(arr, 0, i -1);
    for (int j =0; j<i; j++){
        cout<<arr[j]<<" ";
    }

}