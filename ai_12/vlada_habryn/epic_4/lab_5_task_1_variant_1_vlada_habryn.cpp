#include <iostream>
using namespace std;

int getWord(char row[], int pos, char word[]) {
    while (row[pos] == '0') {
        pos++;
    }

    if (row[pos] == '\0') {
        return -1;
    }

    int k = 0;

    while (row[pos] != '0' && row[pos] != '\0') {
        word[k] = row[pos];
        pos++;
        k++;
    }
    word[k] = '\0';
    return pos;
}
int main() {
    char a[10][61];
    int n;
    cout << "Enter number of lines: ";
    cin >> n;
    if (n < 1 || n > 10) {
        cout << "Invalid number!" << endl;
        return 1;
    }
    for (int i = 0; i < n; i++) {
        cin.width(61);
        cin >> a[i];
    }
    char word[61];
    int lineLength = 0;
    for (int i = 0; i < n; i++) {
        int pos = 0;
        bool hasWord = false;

        if (lineLength == 60) {
            cout << endl;
            lineLength = 0;
        }
        cout << "(";
        lineLength++;
        while (pos != -1) {
            pos = getWord(a[i], pos, word);
            if (pos != -1) {
                if (hasWord) {
                    if (lineLength == 60) {
                        cout << endl;
                        lineLength = 0;
                    }
                    cout << ",";
                    lineLength++;
                }
                for (int j = 0; word[j] != '\0'; j++) {
                    if (lineLength == 60) {
                        cout << endl;
                        lineLength = 0;
                    }
                    cout << word[j];
                    lineLength++;
                }
                hasWord = true;
            }
        }
        if (lineLength == 60) {
            cout << endl;
            lineLength = 0;
        }
        cout << ")";
        lineLength++;
    }
    cout << endl;
    return 0;
}