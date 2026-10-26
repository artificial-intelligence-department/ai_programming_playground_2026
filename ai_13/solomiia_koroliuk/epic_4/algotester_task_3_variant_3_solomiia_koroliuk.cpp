#include <iostream>
#include <string>

using namespace std;

int main(){

    string s;
    cin >> s;

    int c = 1;
    for (int i = 0; i < s.size(); i++){

        if (i + 1 < s.size() and s[i] == s[i + 1]){
            c++;
        }
        else{
            cout << s[i];
            if (c > 1) cout << c;
            c = 1;
        }
        
    }

    return 0;
}