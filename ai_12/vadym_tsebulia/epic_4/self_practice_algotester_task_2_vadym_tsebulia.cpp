#include <iostream>
using namespace std;

int main(){
    int n, m;
    cin >> n;
    cin >> m;
    int a[1000][1000];
    int colMax[1000];
    int rowMin[1000];

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }

    for (int j = 0; j < m; j++){
        int mx = a[0][j];
        for (int i = 1; i < n; i++){
            if (a[i][j] > mx) {
                mx = a[i][j];
            }
        }
        colMax[j] = mx;
    }

    int ansRow = -1;
    for (int i = 0; i < n && ansRow == -1; i++){
        bool ok = true;
        for (int j = 0; j < m; j++){
            if (a[i][j] != colMax[j]){
                ok = false;
                break;
            }
        }
        if (ok) {
            ansRow = i + 1;
        }
    }

    for (int i = 0; i < n; i++){
        int mn = a[i][0];
        for (int j = 1; j < m; j++){
            if (a[i][j] < mn) {
                mn = a[i][j];
            }
        }
        rowMin[i] = mn;
    }

    int ansCol = -1;
    for (int j = 0; j < m && ansCol == -1; j++){
        bool ok = true;
        for (int i = 0; i < n; i++){
            if (a[i][j] != rowMin[i]){
                ok = false;
                break;
            }
        }
        if (ok) {
            ansCol = j + 1;
        }
    }

    cout << ansRow << endl << ansCol << endl;

    return 0;
}