#include <iostream>
#include <vector>
#include <string>
using namespace std;

void answer(const vector<vector<int>>& matrix, int x, int y, int N) {
    if (matrix[x][y] != 0) {
        cout << 1 << "\n";
        cout << matrix[x][y] << "\n\n";
        return;
    }

    bool used[10] = {false};
    for (int i = 0; i < N; i++) {
        used[matrix[x][i]] = true;   // рядок
        used[matrix[i][y]] = true;   // стовпець
    }

    vector<int> res;
    for (int d = 1; d <= N; d++)
        if (!used[d]) res.push_back(d);

    if (res.empty()) {
        cout << 0 << "\n\n";
        return;
    }

    cout << res.size() << "\n";
    for (size_t i = 0; i < res.size(); i++) {
        if (i) cout << ' ';
        cout << res[i];
    }
    cout << "\n\n";
}

int main() {
    int N;
    cin >> N;

    vector<vector<int>> matrix;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;                         // рядок з N цифр без пробілів
        vector<int> row;
        for (int j = 0; j < N; j++) row.push_back(s[j] - '0');
        matrix.push_back(row);
    }

    int Q;
    cin >> Q;
    vector<vector<int>> question;
    for (int i = 0; i < Q; i++) {
        int x, y;
        cin >> x >> y;
        question.push_back({x, y});
    }

    for (int i = 0; i < Q; i++) {
        answer(matrix, question[i][0] - 1, question[i][1] - 1, N);
    }
    return 0;
}