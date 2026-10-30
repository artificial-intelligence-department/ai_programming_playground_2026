/*
    Algotester lab 3
    Михайловська Анна
    ШІ-14
    Варіант 2
*/
#include <iostream>
using namespace std;

int main() {
    int n, m, a[100], b[100];

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cin >> m;
    for (int i = 0; i < m; i++)
        cin >> b[i];

    int common_elements = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i] == b[j]) {
                common_elements++;
            }
        }
    }

    int various_elements = n + m - common_elements;

    cout << common_elements << endl;
    cout << various_elements << endl;

    return 0;
}