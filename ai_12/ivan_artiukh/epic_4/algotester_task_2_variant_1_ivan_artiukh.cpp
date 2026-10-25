#include <iostream>
using namespace std;

int main(){

    int n = 0;
    cin>>n;

    if(n<=1){
        cout<<0;
        return 0;
    }

    int *arr = new int[n];

    for(int i = 0; i < n; i++){
        cin>>arr[i];
    } 

    for(int i = 0; i < n; i++){
        bool swapped = false;
        for(int j = 0; j < n - 1; j++){
            if(arr[j] > arr[j+1]){
                int tmp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = tmp;
                swapped = true;
            }
        }
        if(!swapped) break;
    }

    int case_1 = abs(arr[n-1] - arr[1]);
    int case_2 = abs(arr[n-2] - arr[0]);
    
    cout<<((case_1< case_2)? case_1 : case_2);
    delete[] arr;
    arr = nullptr;
}
