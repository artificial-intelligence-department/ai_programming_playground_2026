//algotester self practice task 1 2045
#include <iostream>
#include <string>

using namespace std;

int main() {
    int k;
    cin >> k;

    int n = 8, m = 8; // Шахівниця завжди 8x8

    // 1. виділяємо пам'ять під board через вказівники
    char** board = new char*[n];
    for (int i = 0; i < n; ++i) {
        board[i] = new char[m + 1];
        for (int j = 0; j < m; ++j) {
            board[i][j] = '.'; // заповнюємо крапками
        }
        board[i][m] = '\0';
    }

    // 2. зчитуємо коней і ставимо 'K' на дошку
    for (int step = 0; step < k; ++step) {
        string pos;
        cin >> pos;
        int col = pos[0] - 'a';          // 'a'->0, 'b'->1 ...
        int row = 8 - (pos[1] - '0');    // '8'->0, '7'->1 ...
        board[row][col] = 'K';
    }

    int vertical[]   = {-2, -2, -1, -1,  1,  1,  2,  2};
    int gorizontal[] = {-1,  1, -2,  2, -2,  2, -1,  1};

    // 3. виділяємо пам'ять під result через вказівники
    char** result = new char*[n];
    for (int i = 0; i < n; ++i) {
        result[i] = new char[m + 1];
        for (int j = 0; j < m; ++j) {
            result[i][j] = '.'; // Початково результуюча дошка теж у крапках
        }
        result[i][m] = '\0';
    }

    // 4. логіка перевірки ходів коня
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (board[i][j] == 'K') {
                for (int step = 0; step < 8; ++step) {
                    int new_i = i + vertical[step];
                    int new_j = j + gorizontal[step];

                    // Перевіряємо межі дошки 8x8
                    if (new_i >= 0 && new_i < n && new_j >= 0 && new_j < m) {
                        result[new_i][new_j] = 'K';
                    }
                }
            }
        }
    }

    // 5. Вивід результату
    for (int i = 0; i < n; ++i) {
        cout << result[i] << "\n";
    }

    // 6. Очищення пам'яті 
    for (int i = 0; i < n; ++i) {
        delete[] board[i];
        delete[] result[i];
    }
    delete[] board;
    delete[] result;

    return 0;
}