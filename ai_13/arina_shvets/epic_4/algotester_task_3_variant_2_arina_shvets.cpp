#include <iostream>

using namespace std;

int main(){
    int n, m;
    int a[100], b[100];
    cin >> n;

    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    cin >> m;

    for (int j = 0; j < m; j++){
        cin >> b[j];
    }

    int common = 0;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (a[i] == b[j]){
                common++;
                break;
            }
        }
    }

    int total = n + m - common;

    cout << common << endl;
    cout << total << endl;

    return 0;
}