//Лотерея
#include <iostream>
using namespace std;
int main() {
    int n, m, a[1000][1000];
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    int answer = 1001;
    for (int j = 0; j < m; j++) {
        int maxNum = a[0][j];
        for (int i = 1; i < n; i++) {
            if (a[i][j] > maxNum) {
                maxNum = a[i][j];
            }
        }
        if (maxNum < answer) {
            answer = maxNum;
        }
    }
    cout << answer << endl;
    return 0;
}