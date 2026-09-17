//Задача №2106 "Замовлення від стоматологів"
#include <iostream>
#include <string>
using namespace std;
int main() {
    int n;
    cin>>n;
    string lowerT, upperT;
    cin>>lowerT>>upperT;
    bool chewing =false;
    for (int i=0; i<n; i++){
        //задаємо умову для випадку, коли є і верхній і нижній зуб
        if (lowerT[i]=='1' && upperT[i]=='1'){
            //змінюємо елемент на true для цієї умови 
            chewing=true;
            break;
        }
    }
    if(chewing){
    cout<<"Yes"<<endl;}
    else{
    cout<<"No"<<endl;}
    return 0;
}
