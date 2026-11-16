/* Task 2023 - Best Battery */

#include <iostream>
#include <string>

using namespace std;

string getBestString(const string& s, char c);

int main() {

    int n;
    if (!(cin >> n)) return 0;

    char c;
    cin >> c;

    string best_overall = "";

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;

        // Знаходимо найкращий результат для поточного акумулятора
        string current_best = getBestString(s, c);

        // Порівнюємо із загальним найкращим результатом
        if (i == 0 or current_best < best_overall) {
            best_overall = current_best;
        }
    }

    cout << best_overall << "\n";

    return 0;
}

// Функція для пошуку найкращого варіанту для конкретного рядка s з додаванням літери c
string getBestString(const string &s, char c) {
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] > c) {
            string temp = s;
            temp.insert(temp.begin() + i, c);
            return temp;
        }
    }
    return s + c;
}
