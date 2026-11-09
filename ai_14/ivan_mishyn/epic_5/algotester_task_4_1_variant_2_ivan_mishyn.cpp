#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int n,k;
    cin>>n>>k;
    int* a = new int[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    sort(a,a+n);
    int* end = unique(a,a+n);
    n = end-a;

    k%=n;
    rotate(a,a+k,a+n);

    cout<<n<<endl;
    for(int i=0;i<n;i++){
        cout<<a[i]<<' ';
    }

    delete[] a;
    a=nullptr;
}