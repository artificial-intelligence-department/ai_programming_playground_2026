/*
Задача:  Дужки і Нобелівська премія
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>

using namespace std;

const int MAX_LENGTH = 255;

bool findBracketPairs(char expression[], int length, int closingPositions[]);
void printBracketPairs(char expression[], int closingPositions[], int left, int right);

int main() {
    char expression[MAX_LENGTH + 1];
    int closingPositions[MAX_LENGTH] = {};

    if (!cin.getline(expression, MAX_LENGTH + 1)) {
        return 0;
    }

    int length = 0;
    while (expression[length] != '\0') {
        length++;
    }

    if (!findBracketPairs(expression, length, closingPositions)) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    printBracketPairs(expression, closingPositions, 0, length);
    return 0;
}

bool findBracketPairs(char expression[], int length, int closingPositions[]) {
    int stack[MAX_LENGTH];
    int count = 0;

    for (int i = 0; i < length; i++) {
        char symbol = expression[i];
        if (symbol == '(' || symbol == '[') {
            stack[count] = i;
            count++;
        }
        else if (symbol == ')' || symbol == ']') {
            if (count == 0) {
                return false;
            }
            count--;
            int opening = stack[count];
            char expected = symbol == ')' ? '(' : '[';
            if (expression[opening] != expected) {
                return false;
            }
            closingPositions[opening] = i;
        }
    }

    return count == 0;
}

void printBracketPairs(char expression[], int closingPositions[], int left, int right) {
    char bracketTypes[] = {'[', '('};

    for (int type = 0; type < 2; type++) {
        for (int i = left; i < right; i++) {
            if (expression[i] == bracketTypes[type] && closingPositions[i] != 0) {
                int closing = closingPositions[i];

                printBracketPairs(expression, closingPositions, i + 1, closing);
                cout << i + 1 << ' ' << closing + 1 << '\n';
                closingPositions[i] = 0;
                i = closing;
            }
        }
    }
}
