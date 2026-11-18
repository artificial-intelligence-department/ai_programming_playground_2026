/*  
Self Practice завдання 2
Ярошенко Володимир 
11 група 
*/
#include <iostream>
#include <cctype>
#include <string>
using namespace std;

bool isPalindrom(const string& word) {
int size = word.size();
if (size == 0) return false;
else  {
for(int i = 0; i< size / 2; i++) {
    if(tolower(word[i]) != tolower(word[size-i-1])) {
    return false;
}
}
}
return true;
}

int main() {
int palin =0;
string line;
while(getline(cin, line)) {
string word = "";
for(int i=0; i<=line.size(); i++) {
if (i < line.size() && isalpha(line[i])) {
        word += line[i];
}
else {
        if (isPalindrom(word)) {
            palin++;
        }
    word = "";
}         
}
}
cout << palin;
    return 0;
}
