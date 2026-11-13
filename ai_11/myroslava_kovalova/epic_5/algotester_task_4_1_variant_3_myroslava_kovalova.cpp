#include <iostream>
#include<algorithm>


bool compare(unsigned short int a,unsigned short int b){
    return a>b;
}

using namespace std;
int main(){
    short int N;
    cin>>N;
    unsigned short int arr[1000]={0};
    for (int i = 0; i<N; i++){
        cin>>arr[i];
    }

    int start = 0;
    unsigned short int* end = 0;
    
    end=partition(arr, arr+N, [](int x){return x%3==0;} );
    sort(arr+start, end);
    start=end-arr;
    
    end=partition(arr+start, arr+N, [](int x){return x%3==1;} );
    sort(arr+start, end, compare);
    start=end-arr;

    sort(arr+start, arr+N);

    unsigned short int new_size = unique(arr, arr+N)-arr;

    cout<<new_size<<endl;
    for (int i = 0; i<new_size;i++){
        cout<<arr[i]<< ' ';
    }

    return 0;
}