#include<iostream>
#include<algorithm>

using namespace std;

int main(){
    int n,k,x;
    bool used[101]={false};

    cin>>n>>k;

    for(int i=0; i<n;i++){
        cin>>x;
        used[x]=true;

    }
    //сортування і видалення повторів
    int b[101];
    int m=0;
    for(int i=0; i<101; i++){
        if(used[i]){
            b[m]=i;
            m++;
        }
    }

    int c[101];
    k=k%m;
    for(int i=0;i<m;i++){
        c[(i+m-k)%m]=b[i];
    }


    cout<<m<<endl;

    for(int i=0;i<m;i++){
        cout<<c[i]<<' ';
    }

    return 0;
}