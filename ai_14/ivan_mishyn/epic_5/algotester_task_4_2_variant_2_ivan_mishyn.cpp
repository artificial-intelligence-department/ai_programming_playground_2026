#include <iostream>
using namespace std;


int* deletePovt(int nn, int *a,int n){
    int *b=new int[nn];
    int nb=0;
    for(int i=0;i<n;i++){
        if(a[i]!=-1){
            b[nb]=a[i];
            nb++;
        }
    }
    delete[] a;
    a=nullptr;
    return b;
}

void ruh(int k, int *a, int n){
    int *b = new int[n];
    for(int i = 0; i < n; i++){
        b[i] = a[(i + k) % n];
    }
    for(int i = 0; i < n; i++){
        a[i] = b[i];
    }
    delete[] b;
    b=nullptr;
}


int main(){
    int n,k;
    cin>>n>>k;
    int* a= new int[n];
    int nn=0;//скіки видаляєм
    for (int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<n-1;i++){
        if(a[i]==-1){
            continue;
        }
        for(int j=i+1;j<n;j++){
            if(a[i]==a[j]){
                a[j]=-1;
                nn++;
            }
        }
    }
    a=deletePovt(n-nn,a,n);  
    n-=nn;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(a[j]>a[j+1]){
                int temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
    k%=n;
    ruh(k,a,n);
    cout<<n<<endl;
    for(int i=0;i<n;i++){
        cout<<a[i]<<' ';
    }
    delete[] a;
    a=nullptr;

}