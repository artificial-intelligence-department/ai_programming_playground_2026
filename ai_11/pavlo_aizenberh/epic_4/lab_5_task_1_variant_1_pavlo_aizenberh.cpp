#include <iostream>
using namespace std;

int getWord(const char* line, int startPos, char* word) {
    if (line[startPos] == '\0') {
        return -1;
    }

    int i = startPos;
    int len = 0;

    while (line[i] != '0' && line[i] != '\0') {
        word[len] = line[i];
        len++;
        i++;
    }

    word[len] = '\0';

    if (line[i] == '0') {
        return i + 1;
    }

    return (len > 0) ? i : -1;
}

void printRow(const char* line) {
    cout << "(";
    
    int pos = 0;
    char word[61];
    bool firstWord = true;

    while (pos != -1 && line[pos] != '\0') {
        pos = getWord(line, pos, word);
        
        if (word[0] != '\0') {
            if (!firstWord) {
                cout << ",";
            }
            cout << word;
            firstWord = false;
        }
    }
    
    cout << ")";
}

int main() {
    char arr[3][61];

    for (int i = 0; i < 3; i++) {
        cin >> arr[i];
    }

    for (int i = 0; i < 3; i++) {
        printRow(arr[i]);
    }
    cout << endl;

    return 0;
}