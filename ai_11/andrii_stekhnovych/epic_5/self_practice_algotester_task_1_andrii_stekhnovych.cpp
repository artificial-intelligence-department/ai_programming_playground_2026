// Алфавітна послідовність
#include <string>
#include <iostream>
using namespace std;
int main(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    int longest=1;
    int temp=1;
    for (int i=0; i<n-1; i++) {
        if(s[i+1]>s[i]) {
            temp++;
        } else {
            temp=1;
        }
        if(temp>longest) {
            longest=temp;
        }
    }
    cout << longest;
    return 0;
}