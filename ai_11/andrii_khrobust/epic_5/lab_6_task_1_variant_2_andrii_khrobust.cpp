#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char s[256];
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0';
    int i = 0;
    while (s[i] != '.' && s[i] != '\0') {
        while (s[i] == ' ') {
            i++;
        }
        int start = i;
        bool vowel = false;
        while (s[i] != ' ' && s[i] != '.' && s[i] != '\0') {
            if (strchr("aeiouyAEIOUY", s[i]) != NULL) {
                vowel = true;
            }
            i++;
        }
        if (!vowel && start < i) {
            for (int j = start; j < i; j++) {
                cout << s[j];
            }
            cout << endl;
        }
    }
    return 0;
}