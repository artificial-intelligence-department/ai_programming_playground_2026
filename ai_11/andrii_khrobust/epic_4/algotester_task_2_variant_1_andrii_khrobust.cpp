/*Андрій Хробуст ШІ-11
завдання 2 варіант 1*/ 
#include <iostream>
using namespace std;

 int main(){
    long N=0;
    long r[100000];
    long m;
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>r[i];
    }
    for(int i=0;i<N-1;i++){
        for(int j=0;j<N-i-1;j++){
            if(r[j]>r[j+1]){
                int save =r[j];
                r[j]=r[j+1];
                r[j+1]=save;
            }
        }
    }
   if(N==1){
        cout<<0;
    }
    else{
        int a=r[N-1]-r[1];
        int b=r[N-2]-r[0];
        if(a<b){
            cout<<a;
        }
        else{
            cout<<b;
        }
    }
    return 0;
}