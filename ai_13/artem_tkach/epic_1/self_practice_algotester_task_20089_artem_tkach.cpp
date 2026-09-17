#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {
    int n, m; // Кількість напоїв від Марічки і Зеника
    cin >> n >> m;

    set<string> drinks;
    string name;

    for (int i = 0; i < n + m; i++) {
        cin >> name;
        drinks.insert(name);
    }

    cout << drinks.size();

    return 0;
}