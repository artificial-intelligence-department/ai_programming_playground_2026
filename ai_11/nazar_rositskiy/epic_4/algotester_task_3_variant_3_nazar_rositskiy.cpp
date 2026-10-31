#include <iostream>
#include <string>

using namespace std;

int main(){
    string s;
    string scomp = "";
    cin >> s;
    //cout << s << endl;
    //cout << scomp << endl;
    for(int i = 0; i < s.length(); i++){
        int n = 1;
        //scomp += s[i];
        cout << s[i];
        while (s[i] == s[i+1]){
            i++;
            n++;
        }
        if(n != 1){
            cout << n;
        }    
    }
    //cout << s << endl;
    //cout << scomp << endl;

}