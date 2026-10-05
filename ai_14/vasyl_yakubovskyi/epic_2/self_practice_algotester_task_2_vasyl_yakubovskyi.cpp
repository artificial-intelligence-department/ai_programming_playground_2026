/*
Task: self_practice_algotester_task_2 (Музикант мобільний)
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/
#include <iostream>

using namespace std;
int main (){
    
    long long s = 0;
    cin >> s;
    long long n = (s + 59) / 60;
    if(n<=7){
        long long totalprice = 11 + n*9;
        cout << totalprice << endl;
    }else if(n > 7){
        long long first7 = (n - (n-7))*9;
        long long other = (n-7)*5;
        long long totalprice = 11 + first7 + other;
        cout << totalprice << endl;
    }else{
        return 0;
    }

    return 0;
}
