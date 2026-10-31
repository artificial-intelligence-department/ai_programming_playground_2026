#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore();

    int count = 0;
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        for (int j = 0; j < line.size(); j++) {
            if (line[j] == '#' && (j == 0 || line[j - 1] != '#')) {
                count++;
            }
        }
    }

    cout << count;
    return 0;
}