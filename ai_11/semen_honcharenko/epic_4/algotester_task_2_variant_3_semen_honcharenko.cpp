/*
    Лабораторна робота Алготестер. Завдання 2. Варіант 3.
    Гончаренко Семен
    ШІ-11
*/
#include <iostream>
using namespace std;

int main() {
    int N = 0;
    while (!(cin >> N) or N < 1 or N > 100) {
        cin.clear();
        cin.ignore(1000, '\n');
    }
    int arr[N] = {};
    for (int i = 0; i < N; ++i) {
    arr_input:
        cin >> arr[i];
        if (arr[i] < 1 or arr[i] > 5 or cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            goto arr_input;
        }
    }
    int drone1_pos = 1;
    int drone2_pos = N;

    while (true) {
            if (drone1_pos == drone2_pos) {
            cout << drone1_pos << " " << drone2_pos << "\n";
            cout << "Collision\n";
            return 0;
        }
        if (drone1_pos > drone2_pos) {
            cout << drone1_pos << " " << drone2_pos << "\n";
            cout << "Miss\n";
            return 0;
        }
        if (drone1_pos+1 == drone2_pos) {
            cout << drone1_pos << " " << drone2_pos << "\n";
            cout << "Stopped\n";
            return 0;
        }
        drone1_pos += arr[drone1_pos-1];
        drone2_pos -= arr[drone2_pos-1];
    }
}