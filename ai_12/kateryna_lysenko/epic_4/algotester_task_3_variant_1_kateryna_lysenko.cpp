/*
Назва:Task 3
Автор: Катерина Лисенко
Група: ШІ-12
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;

    cin.ignore();

    int result = 0;

    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);

        for (int j = 0; j < line.length(); j++) {
            if (line[j] == '#' &&
                (j == 0 || line[j - 1] != '#')) {
                result++;
            }
        }
    }

    cout << result << endl;

    return 0;
}

