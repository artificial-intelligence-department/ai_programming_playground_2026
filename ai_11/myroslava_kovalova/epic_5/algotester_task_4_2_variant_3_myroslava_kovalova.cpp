#include <iostream>


int part_by_3(unsigned short int arr[],int insert_index, int N, int k){
    unsigned short int temp;
    for (int i = insert_index; i< N; i++ ){
        if (arr[i]%3==k){
            temp = arr[insert_index];
            arr[insert_index]=arr[i];
            arr[i]=temp;
            insert_index++;
        }
        
    }
    return insert_index;
}
int partion(unsigned short int arr[],int start, int end, bool ascendic){
    int insert_index = start;
    int pivot = end;
    for (int i = start; i< end; i++){
        bool condition = ascendic? arr[i]<arr[pivot]:arr[i]>arr[pivot];
        if (condition){
            unsigned short int temp = arr[insert_index];
            arr[insert_index]=arr[i];
            arr[i]=temp;
            insert_index++;
        }
    }
    unsigned short int temp = arr[insert_index];
    arr[insert_index]= arr[pivot];
    arr[pivot]=temp;
    return insert_index;
}
void quickSort(unsigned short int arr[],int start, int end, bool ascendic){
    if (start>=end) return;
    int pivot = partion(arr, start, end, ascendic);
    quickSort(arr,start, pivot-1,ascendic );
    quickSort(arr,pivot+1, end, ascendic);

}

using namespace std;
int main(){
    short int N;
    cin>>N;
    unsigned short int arr[1000]={0};
    for (int i = 0; i<N; i++){
        cin>>arr[i];
    }
    int start =0, end= N;
    
    end=part_by_3(arr, start, N, 0);
    quickSort(arr,start, end-1, true);
    start=end;
    
    end=part_by_3(arr, start, N, 1);
    quickSort(arr,start, end-1, false);
    start=end;

    end=part_by_3(arr, start, N, 2);
    quickSort(arr,start, end-1, true);

    unsigned short int copy[1000]={0};
    copy[0]=arr[0];
    int duplicate =1;
    for (int i = 1; i<N; i++){
        if (copy[duplicate-1]!=arr[i]){
            copy[duplicate]=arr[i];
            duplicate++;
        }
    }
    cout<<duplicate<<endl;
    for (int i =0; i<duplicate; i++){
        cout<<copy[i]<<" ";
    }
    return 0;
}