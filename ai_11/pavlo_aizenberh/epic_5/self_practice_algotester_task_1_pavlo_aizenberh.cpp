//"Снігурочка"

#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(string str){
    int len = str.length();
    int i = 0;
    int j = len - 1;
    while (i < j){
        if (str[i] != str[j]) return false;
        j--;
        i++;
    }
    return true;
}

int main(){
    int count = 0;
    string word;

    while (cin >> word){
        int length = word.length();
        for (int i = 0; i < length; i++){
            word[i] = tolower(word[i]);
        }
        if (isPalindrome(word))count++;
    }
    cout << count;
}