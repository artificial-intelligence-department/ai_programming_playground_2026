/*
Завдання: Лотерея
*/
#include <iostream>
#include <algorithm>
using namespace std;
int main(){
 int rows, cols;
 cin >> rows >> cols;
 int* col_max = new int[cols]();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int val;
            cin >> val;
            if (val > col_max[j]) {
                col_max[j] = val;
            }
        }
    }

    int min = col_max[0];
    for (int j = 1; j < cols; j++) {
        if (col_max[j] < min) {
            min = col_max[j];
        }
    }

    cout << min << "\n";

    delete[] col_max;
    return 0;
}