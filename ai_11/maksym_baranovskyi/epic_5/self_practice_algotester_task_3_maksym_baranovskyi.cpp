//Погане слово
#include <iostream>
#include <string>
using namespace std;

string s;

bool isPalindrome(int start, int end){
    while(start < end){
        if(s[start] != s[end]) return false;
        start++;
        end--;
    }
    return true;
}

int main(){

    int n;
    cin >> n >> s;

    if(!isPalindrome(0, n-1)){
        cout << 1;
        return 0;
    }

    int sameAmount = 0;
    while(sameAmount < n && s[sameAmount] == s[0]){
        sameAmount++;
    }

    if(sameAmount == n){
        cout << -1;
        return 0;
    }

    for(int k = sameAmount + 1; k <= sameAmount + 2; k++){
        if(k < n && !isPalindrome(0, k - 1) && !isPalindrome(k, n - 1)){
            cout << 2;
            return 0;
        }
    }

    cout << -1;
    
    return 0;
}