/*
Епік 4. Завдання з Алготестера. Лабораторна робота №3. Варіант №3
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include <iostream>
#include <string>
using namespace std;

int main() {

    string S;
    cin >> S;

    if (S.length() > 100000) return 1;

    string result = "";
    int count = 1;

    for (int i = 1; i < S.length(); i++) {

        if (S[i] == S[i-1]) {
            count++;
        }
        else {
            result += S[i-1];

            if (count > 1) {
                result += to_string(count);
            }

            count = 1;
        }
    }

    result += S[S.length()-1];

    if (count > 1) {
        result += to_string(count);
    }

    cout << result << "\n";

    return 0;
}
