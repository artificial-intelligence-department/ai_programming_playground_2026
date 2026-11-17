#include <iostream>
using namespace std;

const int maxn=1000;
void sort(int a[], int n){
    for (int i=1; i<n; i++){
        int k=a[i];
        int j=i-1;
        while (j>=0 && a[j]>k){
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=k;
    }
}
int unique (int a[], int n){
    if (n==0){
        return 0;
    }
    int len=1;
    for (int i=1; i<n; i++){
        if (a[i]!=a[len-1]){
            a[len]=a[i];
            len++;
        }
    }
    return len;
}
void reverse(int a[], int l, int r){
    while (l<r){
        int t=a[l];
        a[l]=a[r];
        a[r]=t;
        l++;
        r--;
    }
}
void rotate(int a[], int n, int k){
    k%=n;
    if (k==0) return;
    reverse(a,0,k-1);
    reverse(a,k,n-1);
    reverse(a,0,n-1);
}
int main()
{
    int n,k;
    cin>>n>>k;
    int a[maxn];
    for (int i=0; i<n; i++){
        cin>>a[i];
   }
   sort(a,n);
   int m=unique(a,n);
   rotate(a,m,k);
   cout<<m<<'\n';
   for (int i=0; i<m; i++)
   {
    if (i>0){
        cout<<" ";
    }
    cout<<a[i];
   }
   cout<<'\n';

}