#include <iostream>
using namespace std;

int main() {
    int s_1, s_2, v;

    cin >> s_1 >> s_2 >> v;

    if (s_1 < 4 *s_2){
        v = 2 * v;
        cout << "Down" << endl;
    }
    else if (s_1 > 4 *s_2){
        v = v / 2;
        cout << "Up" << endl;
    }
        else {
            cout << "Never mind" << endl;
        }
        return 0;
    }