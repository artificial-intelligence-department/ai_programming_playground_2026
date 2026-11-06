/*Андрій Хробуст ШІ-11
завдання 3 варіант 3*/ 
#include <iostream>
#include <string>
using namespace std;

int main(){
    string s;
    int count = 1;
    cin >> s;
    for(int i = 0; i < s.length()-1; i++){
        if(s[i] == s[i+1]){
            count++;
        }
        else{
            cout << s[i];
            if(count > 1){
                cout << count;
                count=1;
            }
            else
            count = 1;
        }
    }
    cout << s[s.length()-1];
         if(count > 1){
         cout << count;
         }
    return 0;
}
