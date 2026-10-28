/*
Назва задачі: Зеник-садівник
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>

using namespace std;

int main() {

int n, m;
cin >> n >> m;
char a[100][100] = {};

for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        if ((i / 2 + j) % 2 == 0) {
            a[i][j] = 'x';
        }

        else {
            a[i][j] = 'o';
        }
    }
}

for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        cout << a[i][j];
    }
    cout << endl;
}

return 0;
}