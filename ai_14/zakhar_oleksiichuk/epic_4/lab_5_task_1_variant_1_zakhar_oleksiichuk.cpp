/*
Олексійчук Захар ШІ-14
*/

#include <iostream>
#include <cstring>

using namespace std;

bool FindWord(char matrix[][50], int rows, int cols, int &row, int &col, char word[]) {
    memset(word, 0, 50);
    int wordInd = 0;
    while (row < rows){
        while (col < cols) {
            char ch = matrix[row][col];
            if (ch == '\0') {
                break;
            }
            col++;
            if (ch == '0') {
                word[wordInd] = '\0';
                return true;
            }
            else {
                word[wordInd] = ch;
                wordInd++;
            }
        }
        row++;
        col=0;
    }
    return false;
}

void PrintWords(char matrix[][50], int rows, int cols) {
    char word[50];
    int r = 0;
    int c = 0;
    int lineLength = 0;
    bool firstWord = true;
    int prevRow = 0;

    cout << "(";
    lineLength++;

    while(FindWord(matrix, rows, cols, r, c, word)) {
        int len = strlen(word);

        if (r != prevRow) {
            cout << ") (";
            prevRow = r;
            lineLength = 1;
            firstWord = true;
        }

        if (!firstWord && lineLength + len + 1 > 60) {
            cout << ") (";
            firstWord = true;
            lineLength = 1;
        }

        if (!firstWord) {
            cout << ", ";
        }

        cout << word;
        lineLength += len;
        firstWord = false;
    }

    cout << ")\n";
}

int main() {
    const int ROWS = 3;
    const int COLS = 50;

    char matrix[ROWS][COLS] = {
        {"123023402303450"},
        {"234450234567010"},
        {"234455677670450"}
    };

    cout << "Original: " << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << matrix[i][j];
        }
        cout << endl;
    }

    cout << "After formatting:" << endl;
    PrintWords(matrix, ROWS, COLS);
}