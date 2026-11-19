//Снігурочка
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string line[1024];
int k = 0;  

bool isPalindrome(const string word){
    for(int i = 0; i < word.length(); i++){
        if(word[i] != word[word.length() - 1 - i]){
            return false;
        }
    }
    return true;
}

string toLower(const string word){
    string res;
    for(char c: word){  
        res += tolower(c);
    }
    return res;
}

int main(){

    string s;
    while(k < 1024 && getline(cin, s)){
        line[k] = s;
        k++;
    }

    int ans = 0;
    for(int i = 0; i < k; i++){        
        string word = "";
        for(int j = 0; j <= line[i].length(); j++){
            if(j == line[i].length() || line[i][j] == ' '){
                if(word.length() > 0 && isPalindrome(toLower(word))){
                    ans++;
                }
                word = "";
            }
            else{
                word += line[i][j];
            }
        }
    }

    cout << ans;

    return 0;
}