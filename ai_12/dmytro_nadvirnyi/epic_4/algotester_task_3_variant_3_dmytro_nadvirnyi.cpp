/* lab 3v3  */

#include <iostream>
#include <string>
using namespace std;

void countletters(string s, string &result) {
    int count = 1;
    for (int i = 0; i < s.length() - 1; i++) {
        if (s[i] == s[i+1]){
            count++;
        } else {
            if (count > 1) {
                result += s[i];
                result += to_string(count);
            } else {
                result += s[i];
            }
            count = 1;
            
        }
    }
    if (count > 1) {
        result += s[s.length()-1];
        result += to_string(count);
    } else {
        result += s[s.length()-1];
    }
    cout << result << endl;
}
int main() {
    string s;
    string result;
    cin >>s;

    countletters(s, result);

    return 0;
}