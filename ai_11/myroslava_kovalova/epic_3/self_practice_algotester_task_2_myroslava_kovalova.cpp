#include <iostream>

using namespace std;
int main(){
    int array[1000000]={0};
    int n =0;
    cin>>n;
    for (int i = 0; i<n;i++){
        cin>>array[i];
    }
    int min = array[0];
    int count = 1;
    for (int i =1; i<n; i++){
        if (array[i]<=min) {
            count++;
            min=array[i];
        }
    }
    cout<<count;
    return 0;
}