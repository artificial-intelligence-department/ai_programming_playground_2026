//Снігурочка
#include <iostream>
#include <string>
using namespace std;
int main()
{
    int mark = 0;
    string word;
    while(cin >> word){
        bool isPalindrome = true;
        int i = 0;
        int j = word.size() - 1;
        while(i < j){
            if(tolower(word[i]) != tolower(word[j])){
                isPalindrome = false;
            }
            i++;
            j--;
        }
        if(isPalindrome){
            mark++;
        }
    }
    cout << mark;
}
