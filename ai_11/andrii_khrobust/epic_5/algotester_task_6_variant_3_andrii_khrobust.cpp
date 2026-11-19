#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    if(n < 1 || n > 9) {
        return 0;
    }
    int a[10][10];
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            char x;
            cin >> x;
            a[i][j] = x - '0';
        }
    }
    int q;
    cin >> q;
    for(int k = 0; k < q; k++) {
        int x, y;
        cin >> x >> y;
        if(x < 1 || x > n || y < 1 || y > n) {
            return 0;
        }
        int cnt = 0;
        int possible[10];
        if(a[x][y] != 0) {
            cout << 1 << endl;
            cout << a[x][y] << endl;
            continue;
        }
        for(int num = 1; num <= n; num++) {
            bool found = false;
            for(int j = 1; j <= n; j++) {
                if(a[x][j] == num || a[j][y] == num) {
                    found = true;
                    break;
                }
            }
            if(found == false) {
                possible[cnt] = num;
                cnt++;
            }
        }
        cout << cnt << endl;
        for(int i = 0; i < cnt; i++) {
            cout << possible[i] << " ";
        }
        cout << endl;
    }
    return 0;
}