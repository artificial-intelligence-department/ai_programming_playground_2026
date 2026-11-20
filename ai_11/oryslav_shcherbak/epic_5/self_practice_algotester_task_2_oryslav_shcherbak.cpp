#include <iostream>
#include <string>
using namespace std;

int main(){
    string s;
    cin >> s;
    int a[26];
    for(int i = 0; i<26; i++){
        a[i] = 0;
    }
    for(int i = 0; i<s.size(); i++){
        char c = s[i];
        int index = c - 'a';
        a[index] = a[index] + 1;
    }
    int odd = 0;
    for(int i = 0; i < 26; i++){
        if(a[i]%2 == 1){
            odd++;
        }
    }
    if(odd == 1 || odd == 0){
        cout << "YES";
    }
    else{
        cout << "NO";
    }
    return 0;
}
