#include <iostream>

using namespace std;

int main(){
    int n;
    cin >> n;

    int r[100000];

    for (int i = 0; i < n; i++){
        cin >> r[i];
    }

    int a, b, c;
    cin >> a >> b >> c;

    int newN = 0;

    for (int i = 0; i < n; i++){
        if (r[i] != a && r[i] != b && r[i] != c){
            r[newN] = r[i];
            newN++;
        }
    }

    int m = 0;

    if (newN > 1){
        m = newN - 1;
    }

    cout << m << endl;

    for (int i = 0; i < m; i++){
        cout << r[i] + r[i + 1];

        if (i < m - 1){
            cout << " ";
        }
    }

    if (m > 0){
        cout << endl;
    }

    return 0;
}