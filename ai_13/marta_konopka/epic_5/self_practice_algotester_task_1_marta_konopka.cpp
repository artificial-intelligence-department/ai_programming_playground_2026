#include<iostream>
#include<cstring>
#include<cctype>
using namespace std;

bool Palindrome(const char* word){
    int left = 0;
    int right = strlen(word) - 1;
    while(right > left){
        char a = tolower(word[left]);
        char b = tolower(word[right]);
        if(a != b){
            return false;
        }
        left++;
        right--;
    }
    return true;

}
int main(){
    char word[1000];
    int count = 0;
    while (cin >> word){
        if(strchr(word, '0')){
            break;
        }
        if(Palindrome(word)){
            count++;
        }
    }
    cout << count;

    return 0;
}
