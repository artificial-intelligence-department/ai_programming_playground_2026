#include <iostream>
#include <cstring> 

using namespace std;


char s[100005];

int main() {
    if (cin >> s) {
        int n = strlen(s); 
        
        for (int i = 0; i < n; ) {
            int j = i;
            
   
            while (j < n && s[j] == s[i]) {
                j++;
            }
            
            int count = j - i;
            cout << s[i];
            
            if (count > 1) {
                cout << count;
            }
            
            i = j;
        }
        cout << "\n";
    }

    return 0;
}