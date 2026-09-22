#include<iostream>
using namespace std;

int main(){
    double d,u,sp,Td,Tu;
    cin>>d>>u>>sp;

    Td=d/sp/2;
    Tu=u/sp*2;

    if (Td<Tu){
        cout<<"Down"<<endl;
        return 0;
    }

    if(Tu<Td){
        cout<<"Up"<<endl;
        return 0;
    }
    if(Tu==Td){
        cout<<"Never mind"<<endl;
    }

    return 0;
}
