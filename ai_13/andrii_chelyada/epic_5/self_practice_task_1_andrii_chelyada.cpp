#include <iostream>
#include <string>

using namespace std;

bool isMatching(const string &s1, const string &s2, int l);

int main() {
    int quantity;
    cin >> quantity;

    for(int i = 1; i <= quantity; i++){
        string s1;
        cin >> s1;
        string s2;
        cin >> s2;

        int d = s1.length() - s2.length();
        int k = d / 2;
        if(d % 2 == 0){
            if (isMatching(s1, s2, k) || (isMatching(s1, s2, k - 1) && isMatching(s1, s2, k + 1))){
                cout << "Sergei" << endl;
            }
            else{
                cout << "Larry" << endl;
            }
        }
        else{
            if (isMatching(s1, s2, k) && isMatching(s1, s2, k + 1)){
                cout << "Sergei" << endl;
            }
            else{
                cout << "Larry" << endl;
            }
        }

    }

}

bool isMatching(const string &s1, const string &s2, int l){
    int d = s1.length() - s2.length();
    if(l < 0 || l > d){
        return false;
    }
    else{
        return s1.substr(l, s2.length()) == s2;
    }
}