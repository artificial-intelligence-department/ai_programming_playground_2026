#include <iostream>
#include <string>

using namespace std;

string output(int idx1, int idx2) {
    if (idx1 == idx2) {
        return "Collision";
    } else if (idx1 > idx2) {
        return "Miss";
    } else if ((idx2 - idx1) == 1) {
        return "Stopped";
    } else {
        return "";
    }
}

int main() {
    int N;
    cin >> N;

    int mas[N];
    for (int i = 0; i < N; i++) cin >> mas[i];

    int start_idx = 0, end_idx = N-1;

    for (int i = 0; i < N; i++) {
        string res = output(start_idx, end_idx);
        if (res != "") {
            cout << start_idx + 1 << " " << end_idx + 1 << endl;
            cout << res << endl;
            break;
        }
        start_idx += mas[start_idx];
        end_idx -= mas[end_idx];
    }
}