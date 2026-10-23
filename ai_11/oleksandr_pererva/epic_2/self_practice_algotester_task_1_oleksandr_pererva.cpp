/*
"Камінь-ножиці-папір"
Перерва Олександр
ШІ-11
*/
#include <iostream>

using namespace std;

int main(){
    int rm,sm,pm,rz,sz,pz,win=0;
    cin>>rm>>sm>>pm>>rz>>sz>>pz;
    if(rm>sz){
        win+=sz;
    } else win+=rm;
    if(sm>pz){
        win+=pz;
    } else win+=sm;
    if(pm>rz){
        win+=rz;
    } else win+=pm;
    cout<<win;
    return 0;
}