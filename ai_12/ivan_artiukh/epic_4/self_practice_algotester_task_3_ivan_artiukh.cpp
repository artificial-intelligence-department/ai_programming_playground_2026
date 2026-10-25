//cards
#include <iostream>
using namespace std;

void push(int *&a, int &n, int el) {
    int *b = new int[n + 1];
    for (int i = 0; i < n; i++) {
        b[i] = a[i];
    }
    b[n] = el;
    delete[] a;
    a = b;
    b = nullptr;
    n++;
}
int main() {
    int w, n;
    cin >> w >> n;
    int *a =  new int[n + 1];
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    if (w > sum) {
        cout << 0 << "\n";
        return 0;
    }

    int target = sum - w;

    int **dp = new int*[n+1];
    for(int i = 0; i < n+1; i++){
        dp[i] = new int[target + 1];
        for(int j = 0; j < target + 1; j++){
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= target; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= a[i]){
                dp[i][j] += dp[i - 1][j - a[i]];
            }
            if (dp[i][j] > 2){
                dp[i][j] = 2;
            }
        }
    }

    if (dp[n][target] == 0) {
        cout << 0 << "\n";
    } else if (dp[n][target] > 1) {
        cout << -1 << "\n";
    } else {
        int *res = new int[0];
        int size = 0;
        int cur = target;
        for (int i = n; i >= 1; i--) {
            if (dp[i - 1][cur] == 1) continue;
            push(res, size, i);
            cur -= a[i];
        }
        for(int i = 0; i < size / 2; i++){
            int tmp = res[i];
            res[i] = res[size - 1 - i];
            res[size - 1 - i] = tmp;
        }
        for (int i = 0; i < size; i++) cout << res[i] << " ";
        cout << "\n";
            delete[] res;
        res = nullptr;
    }
    for(int i = 0; i < n+1; i++){
        delete[] dp[i];
    }
    delete[] dp;
    dp = nullptr;
    delete[] a;
    a = nullptr;
    return 0;
}
