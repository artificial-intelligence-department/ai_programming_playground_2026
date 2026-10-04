/*
Lab 1v3
Піраміда з кубів
Цебуля Вадим
ШІ-12
*/

#include <iostream>
using namespace std;
int main() {
        // Зчитування та перевірка 1-го (найнижчого) куба
        long long cube_1; // Використовуєм long long оскільки до 10^12 int не витримає
        cin >> cube_1;
        if (cube_1 <= 0){
                cout << "ERROR" << endl; 
                return 0;
        }
        // Перевірка 2-го куба: має бути додатним і не більшим за 1-й
        long long cube_2;
        cin >> cube_2;
        if (cube_2 <= 0){
                cout << "ERROR" << endl;
                return 0;
        }
        else if(cube_2 > cube_1){
                cout << "LOSS" << endl;
                return 0;
        }
        // Перевірка 3-го куба: має бути додатним і не більшим за 2-й
        long long cube_3;
        cin >> cube_3;
        if (cube_3 <= 0){
                cout << "ERROR" << endl;
                return 0;
        }
        else if(cube_3 > cube_2){
                cout << "LOSS" << endl;
                return 0;
        }
        // Перевірка 4-го куба: має бути додатним і не більшим за 3-й
        long long cube_4;
        cin >> cube_4;
        if (cube_4 <= 0){
                cout << "ERROR" << endl;
                return 0;
        }
        else if(cube_4 > cube_3){
                cout << "LOSS" << endl;
                return 0;
        }
        // Перевірка 5-го куба: має бути додатним і не більшим за 4-й
        long long cube_5;
        cin >> cube_5;
        if (cube_5 <= 0){
                cout << "ERROR" << endl;
                return 0;
        }
        else if(cube_5 > cube_4){
                cout << "LOSS" << endl;
                return 0;
        }

        // Усі умови виконано — піраміда стійка
        else {
                cout << "WIN" << endl;
                return 0;
        }

        return 0;
}