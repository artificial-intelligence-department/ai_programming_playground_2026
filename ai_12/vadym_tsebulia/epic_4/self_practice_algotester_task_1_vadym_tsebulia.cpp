#include <iostream>
#include <string>
using namespace std;

int main() {

    int n;
    cin >> n;
    char a[1000][1000];
    for (int i = 0; i < n; ++i){
        string row;
        cin >> row;
        for (int j = 0; j < n; ++j){
            a[i][j] = row[j];
        }
    }

    for (int i = 0; i < n; ++i){
        for (int j = i + 1; j < n; ++j){
            if (a[i][j] != a[j][i]){
                cout << "No" << endl;
                return 0;
            }
        }
    }

    cout << "Yes" << endl;
    return 0;
}