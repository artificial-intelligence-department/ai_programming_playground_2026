/*Algotester Task 3 Variant 3
Автор:Сенько Вікторія
Група: ШІ-12 group3*/
#include <iostream>
#include <string>
using namespace std;
int main() {
    string S = " ";
    cin >> S;
    int count = 1;
    for(int i = 1; i <= S.length(); i++){
        if(i< S.length() && S[i]==S[i-1]) count++;
        else{
            cout<<S[i-1];
            if(count>1) cout << count;
            count = 1;
        } 
    }
    cout<< endl;
    return 0;
}