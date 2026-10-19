/*
Task: self_practice_algotester_task_2 (Коля, Вася і Теніс)
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/

#include <iostream>

using namespace std ;

int main(){

    long long n = 0;
    cin >> n;

    long long V_winsServe = 0;
    long long K_winsServe = 0;

    long long V_wins = 0;
    long long K_wins = 0;

    for (long long i = 0; i < n; i++){
        char serve;
        cin >> serve;

        if (serve == 'V'){ 
            V_winsServe++;
            
        }else if(serve == 'K'){
            K_winsServe++;
        }
        
        if(V_winsServe >= 11 && (V_winsServe - K_winsServe) >=2){
            V_wins++;
            V_winsServe = 0;
            K_winsServe = 0;   
        }
        if(K_winsServe >= 11 && (K_winsServe - V_winsServe) >=2){
            K_wins++;
            V_winsServe = 0;
            K_winsServe = 0;
        }

    }

    cout << K_wins << ":" << V_wins << endl;
    if(K_winsServe > 0 || V_winsServe > 0){
        cout << K_winsServe << ":" << V_winsServe << endl;
    }
    

    return 0;
}