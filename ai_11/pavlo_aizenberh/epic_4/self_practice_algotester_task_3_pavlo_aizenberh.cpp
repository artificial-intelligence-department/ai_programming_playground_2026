//2102 - Orders from florists
//https://algotester.com/en/ContestProblem/DisplayWithEditor/167969
#include <iostream>
using namespace std;

int a[105][105];
int rowSum[105];
int colSum[105];

int main() {

    int n, m;
    cin >> n >> m;
    
    for (int i = 0; i < n; i++) rowSum[i] = 0;
    for (int j = 0; j < m; j++) colSum[j] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            rowSum[i] += a[i][j];
            colSum[j] += a[i][j];
        }
    }

    int maxFlowers = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int current = rowSum[i] + colSum[j] - a[i][j];
            if (current > maxFlowers) {
                maxFlowers = current;
            }
        }
    }

    cout << maxFlowers << "\n";

    return 0;
}