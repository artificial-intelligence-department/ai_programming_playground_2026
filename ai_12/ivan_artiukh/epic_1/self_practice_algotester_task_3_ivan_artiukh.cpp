#include <iostream>
#include <cmath>


using namespace std;
int main(){
    int n = 0;
    int k = 0;
    int m1=0, m2=0;
    cin>>n>>k;
    int arr[n];
    for( int i=0; i<n; i++){
        cin>>arr[i];
        if(arr[i]>=k){
            m1++;
        }
        else if(arr[i]<k){
            if(m1>m2){
                m2=m1;
            }
            m1=0;
        }
    }
    cout<<max(m1,m2);

}
