// Патріотична стрічка
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main(){
    string s;
    cin >> s;
    int cntYB = 0;
    int cntBY = 0;

    for(int i = 0; i < s.length(); i++){
        if(i%2 == 0){
            if(s[i] != 'B') cntBY++;
            if(s[i] != 'Y') cntYB++;
        }else{
            if(s[i] != 'Y') cntBY++;
            if(s[i] != 'B') cntYB++;
        }
    }

    cout << min(cntYB, cntBY);

    return 0;
}