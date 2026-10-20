/*
<Белаш Матвій ШІ-12
Завдання з алготестеру "Коля, Вася і Теніс"
*/
#include <iostream>
using namespace std;

int main(){

    int n;
    cin >> n; 
    char c[n];
    int rv = 0;
    int rk = 0;
    int vrk = 0;
    int vrv = 0;
    for(int i = 0; i < n; i++){
        cin >> c[i];
    }
    for(int i = 0; i < n; i++){
        if(c[i] == 'V'){
            rv +=1;
        }else if(c[i] == 'K'){
            rk +=1;
        }
        if((rv >= 11 || rk >= 11) && (rv - rk >= 2 || rk - rv >= 2)){ 
            if(rv - rk >= 2){
                vrv += 1;
            }else{
                vrk += 1;
            }
            rk = 0;
            rv = 0;
        }
    }
    cout << vrk << ":" << vrv << endl;
    if(rv != 0 || rk != 0){
        cout << rk << ":" << rv << endl;
    }

    return 0;
}