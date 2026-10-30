// Алготестер Lab 3v3
// Стехнович ШІ-11
#include <iostream>
using namespace std;
int main(){
    char s[100000] = {0};
    cin >> s;
    char prev = s[0];
    int char_counter = 0;
    for (char s_1 : s) {
        if (s_1!=prev) {
            if (char_counter>1) {
                cout<<prev<<char_counter;
            }
            else {
                cout<<prev;
            }
            char_counter=0;
        }
        char_counter++;
        prev=s_1;
    }
    
    cout<<endl;
    return 0;
}