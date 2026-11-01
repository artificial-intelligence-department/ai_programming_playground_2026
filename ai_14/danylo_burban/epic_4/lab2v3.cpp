#include <iostream>

using namespace std;

int main(){
    int N;
    cin>>N;
    int *arr= new int[N];
    for (int i=0; i<N;i++){
        cin>>arr[i];
    }
    int pos1=0;
    int pos2=N-1;

    while (true)
    {
        if(pos1>pos2){
            cout<<pos1+1<<" "<<pos2+1<<endl;
            cout<<"Miss"<<endl;
            
            break;
        }
        if(pos1==pos2){
            cout<<pos1+1<<" "<<pos2+1<<endl;
            cout<<"Collision"<<endl;
            
            break;
        }
        if(pos1+1==pos2){
            cout<<pos1+1<<" "<<pos2+1<<endl;
            cout<<"Stopped"<<endl;
            
            break;
        }
        pos1=pos1+arr[pos1];
        pos2=pos2-arr[pos2];
    }
    

    delete[] arr;
}