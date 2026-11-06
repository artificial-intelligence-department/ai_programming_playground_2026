/*
    Лабораторна робота Алготестер. Завдання 3. Варіант 1.
    Гончаренко Семен
    ШІ-11
*/
#include <iostream>
#include <string>
using namespace std;

int main() {
    int N = 0;
    cin >> N;

    string spell;
    getline(cin, spell); // removes "\n"(Enter) from the input

    int fix = 0;

    for (int i = 0; i < N; ++i) {
        getline(cin, spell);
        bool damaged_now = 0;
        
        for (char s : spell) {
            if (s == '#') {
                if (damaged_now == 0) {
                    damaged_now = 1;
                    fix++;
                }
            }
            else {
                damaged_now = 0;
            }
        }
    }
    cout << fix << "\n";
    return 0;
}