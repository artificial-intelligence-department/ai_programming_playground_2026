/*
Задача:  Конкурс талантів
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>

using namespace std;

int countBags(char garage[][10], int row, int column, int size);

int main() {
    int garageSize;
    int bagLimit;
    char garage[10][10];

    cin >> garageSize >> bagLimit;

    for (int row = 0; row < garageSize; row++) {
        for (int column = 0; column < garageSize; column++) {
            cin >> garage[row][column];
        }
    }

    int maximum = 0;

    for (int size = 1; size <= garageSize; size++) {
        for (int row = 0; row + size <= garageSize; row++) {
            for (int column = 0; column + size <= garageSize; column++) {
                int bags = countBags(garage, row, column, size);

                if (bags <= bagLimit && size > maximum) {
                    maximum = size;
                }
            }
        }
    }

    cout << maximum << endl;

    return 0;
}

int countBags(char garage[][10], int row, int column, int size) {
    int bags = 0;

    for (int i = row; i < row + size; i++) {
        for (int j = column; j < column + size; j++) {
            if (garage[i][j] == '1') {
                bags++;
            }
        }
    }

    return bags;
}