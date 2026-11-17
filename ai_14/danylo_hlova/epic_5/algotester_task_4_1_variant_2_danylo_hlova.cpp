#include<iostream>
#include<algorithm>

using namespace std;

int main(){
    int n,k;
    int a[1000];
    cin>>n>>k;

    for(int i=0; i<n;i++){
        cin>>a[i];
    }
    sort(a,a+n);
    int* end = unique(a,a+n);
    n=end-a;    
    k=k%n;
    rotate(a, a+k, a+n);

    cout<<n<<endl;

    for(int i=0;i<n;i++){
        cout<<a[i]<<' ';
    }

    return 0;
}