/*
Белаш Матвій ШІ-12
Завдання з алготестеру "Повний чіназес"
*/
#include <iostream>
#include <string>
using namespace std; 


int main(){

    int n = 0;
    int balance = 0;
    cin >> n;
    string N[n];
    int z = 0;
    bool dolg = false;
    for(int i =0; i < n; i++){
        cin >> N[i];
        cin >> z;
        if(N[i] == "earn"){
            balance += z;
        }
        if(N[i] == "spend"){
            balance -= z;
        }
        if(balance < 0){
            dolg = true;
        }
    }
    if(dolg == true){
        cout << "debt";
        return 0;
    }
    
    cout << "chinazes";
    return 0;
}