#include <iostream>
#include <string>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    string names[1000];       
    int total = n + m;
    for (int i = 0; i < total; i++) {
        cin >> names[i];
    }
    int count = 0;
    for (int i = 0; i < total; i++) {
        bool wasBefore = false;
        for (int j = 0; j < i; j++) {
            if (names[j] == names[i]) {
                wasBefore = true;
                break;
            }
        }
        if (!wasBefore) {
            count++;
        }
    }
    cout << count << endl;
    return 0;
}