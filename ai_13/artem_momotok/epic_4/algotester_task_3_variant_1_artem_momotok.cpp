/*
    Algotester Lab 3v1, Момоток Артем, ШІ-13
*/
#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore(); // пропускаємо кінець рядка після N

    int rituals = 0;
    string line;
    for (int k = 0; k < n; k++) {
        getline(cin, line);
        for (size_t i = 0; i < line.size(); i++) {
            if (line[i] == '#' && (i == 0 || line[i - 1] != '#')) {
                rituals++;
            }
        }
    }

    cout << rituals << endl;
    return 0;
}