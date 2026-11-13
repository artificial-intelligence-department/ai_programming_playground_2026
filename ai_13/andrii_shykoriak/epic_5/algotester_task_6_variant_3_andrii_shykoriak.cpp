#include <iostream>
#include <string>
using namespace std;

int main() {
    int N;
    cin >> N;
    int **matrix = new int*[N];
    for (int i = 0; i < N; i++)
    {
        matrix[i] = new int[N];
    }

    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < N; j++) {
            matrix[i][j] = s[j] - '0';
        }
    }
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        if (matrix[x][y] == 0) {
            int found = 0;
            int row[10] = {};
            int col[10] = {};
            for (int j = 0; j < N; j++)
            {
                if (matrix[x][j] != 0)
                    row[matrix[x][j]] = 1;

                if (matrix[j][y] != 0)
                    col[matrix[j][y]] = 1;
            }
            for (int k = 1; k <= N; k++)
            {
                if (row[k] == 0 && col[k] == 0)
                    found++;
            }
            cout << found << endl;
            if (found > 0) {
                for (int k = 1; k <= N; k++) {
                    if (row[k] == 0 && col[k] == 0) {
                        cout << k << " ";
                    }
                }
                cout << endl;
            }
        }
        else {
            cout << 1 << endl;
            cout << matrix[x][y] << endl;
        }
    }
    for (int i = 0; i < N; i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;

    return 0;
}
