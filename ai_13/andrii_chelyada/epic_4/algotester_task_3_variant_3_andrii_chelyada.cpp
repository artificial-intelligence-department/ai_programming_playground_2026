// Algotester Lab 3v3, Челяда Андрій, ШІ-13

#include <iostream>
#include <string>
using namespace std;

int main(){
    string s;
    cin >> s;
    int count = 1;

    for(int i = 1; i < s.length(); i++){
        if (s[i] == s[i - 1]){
            count++;
        }
        else{
            cout << s[i - 1];
            if(count > 1){
                cout << count;
            }
            count = 1;
        }
    }

    cout << s[s.length() - 1];
    if(count > 1){
        cout << count;
    }
    return 0;
}