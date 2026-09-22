#include <iostream>
#include <string> 
using namespace std;

int main() {
    int n;
    cin >> n;

    string s; 
    cin >> s;
    
    int sets_k = 0;
    int sets_v = 0;

    int current_k = 0;
    int current_v = 0;
     
    for ( int i = 0; i < n; i++) {
    if (s[i] == 'K') {
        current_k++;}
    else if (s[i]=='V') {
        current_v++;}
    
    
    if (current_k >= 11 && current_k - current_v >= 2) {
        sets_k++;
        current_k = 0;
        current_v = 0;
    }
    else if (current_v >= 11 && current_v - current_k >= 2) {
        sets_v++;
        current_k = 0;
        current_v = 0;
    }
    }
    cout << sets_k << ":" << sets_v << endl;
    if (current_k >0 || current_v > 0) {
        cout <<current_k << ":" << current_v <<endl;
    }

    return 0;
}