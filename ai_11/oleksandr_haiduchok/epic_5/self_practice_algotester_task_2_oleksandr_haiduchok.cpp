#include <iostream>
#include <string>
#include <cctype>
using namespace std;
int main(){
    string letter;
    int wordcount = 0;
    while(cin >> letter){
        int left = 0;
        int right = letter.length() - 1;
        bool check = true;
        while(left < right){
            if(tolower(letter[left]) != tolower(letter[right])){
                check = false;
                break;
            }
            left++;
            right--;
        }
        if(check == true){
            wordcount++;
        }
    }
    printf("%d", wordcount);
    return 0;
}
