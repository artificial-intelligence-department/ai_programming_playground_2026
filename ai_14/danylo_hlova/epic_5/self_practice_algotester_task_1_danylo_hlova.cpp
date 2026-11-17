#include <iostream>
#include <cctype>
using namespace std;

int main() {
    char s[1100];                      
    int count = 0;

    while (cin >> s) {                  
        int len = 0;
        while (s[len] != '\0') len++;   

        bool pal = true;
        for (int i = 0, j = len - 1; i < j; i++, j--) {
            if (tolower(s[i]) != tolower(s[j])) {
                pal = false;
                break;
            }
        }

        if (pal) count++;
    }

    cout << count << endl;
    return 0;
}