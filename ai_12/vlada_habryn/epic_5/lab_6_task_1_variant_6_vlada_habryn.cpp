#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;
int main() {
    char text[256];
    if (fgets(text, sizeof(text), stdin) == nullptr) {
        return 1;
    }
    text[strcspn(text, "\n")] = '\0';
    cout << "Original text: " << text << endl;
    int length = strlen(text);
    for (int i = 0; i < length - 1; i++) {
        if (!isalpha(text[i])) {
            continue;
        }
        int min = i;
        for (int j = i + 1; j < length; j++) {
            if (!isalpha(text[j])) {
                continue;
            }
            if (text[j] < text[min]) {
                min = j;
            }
        }
        char temp = text[i];
        text[i] = text[min];
        text[min] = temp;
    }
    cout << "Sorted text: " << text << endl;

    return 0;
}
