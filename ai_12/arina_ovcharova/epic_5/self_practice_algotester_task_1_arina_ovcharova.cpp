// Self Practice, задача 1 - "Поле чудес" (Algotester)
// мінімальна кількість ходів = кількість різних букв у слові
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;

    // в слові тільки великі латинські букви
    bool seen[26] = {false};
    int moves = 0;

    for (size_t i = 0; i < s.length(); i++) {
        int c = s[i] - 'A';
        // нову букву ще не називали - рахую хід
        if (!seen[c]) {
            seen[c] = true;
            moves++;
        }
    }

    cout << moves << endl;
    return 0;
}
