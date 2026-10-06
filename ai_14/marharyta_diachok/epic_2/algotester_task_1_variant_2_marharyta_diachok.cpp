/* 
Задача: Algotester Lab №1. Завдання 1. Варіант №2. 
Автор: Дячок Маргарита.
Група: ШІ-14
*/
#include <iostream>
using namespace std;

int main() {
    long long h[4] = {0};
    long long d[4] = {0};
    bool error = false;
    bool perevorot = false;
    long long h_result[4] = {0};
    long long min = 0;
    long long max = 0;

    cin >> h[0] >> h[1] >> h[2] >> h[3];
    cin >> d[0] >> d[1] >> d[2] >> d[3];

    for (int i = 0; i < 4; i++) {
        if (d[i] > h[i]) {
            error = true;
        }
    }

    if (error == true) {
        cout << "ERROR";
        return 0; 
    }

    for (int i = 0; i < 4; i++) {
        h_result[i] = h[i];
    }

    for (int i = 0; i < 4; i++) {
        h_result[i] = h[i] - d[i]; 

        min = h_result[0];
        max = h_result[0];
        
        for (int j = 0; j < 4; j++) {
            if (h_result[j] < min) {
                min = h_result[j];
            }
            if (h_result[j] > max) {
                max = h_result[j];
            }
        }
        
        if (max >= 2 * min) {
            perevorot = true;
        }
    }

    if (perevorot == false && min != 0 && h_result[0] == h_result[1] && h_result[1] == h_result[2] && h_result[2] == h_result[3]) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}