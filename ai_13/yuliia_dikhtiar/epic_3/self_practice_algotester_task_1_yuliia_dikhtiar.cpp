/*
Назва задачі: Повний чіназес
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;

    int balance = 0;
    bool hasDebt = false;

    for (int i = 0; i < n; i++) {
        string action;
        int amount;

        cin >> action >> amount;

        if (action == "earn") {
            balance += amount;
        }
        else if (action == "spend") {
            balance -= amount;
        }

        if (balance < 0) {
            hasDebt = true;
        }
    }

    if (hasDebt) {
        cout << "debt" << endl;
    }
    else {
        cout << "chinazes" << endl;
    }

    return 0;
}
