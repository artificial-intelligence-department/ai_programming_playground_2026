
#include <iostream>
#include <cmath>
#include <string>
using namespace::std;
/* Алготестер лаб 6 варіант 2
   Сідлецький Тимофій ШІ-13*/
int main () {
    cin.tie(nullptr);
    int Q,x,y;
    char board[8][8];
    int req[64][2];
    int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cin >> board[i][j];
        }
    }

    cin >> Q;
    for (int i = 0; i < Q; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> req[i][j];
        }
    }

    for (int i = 0; i < Q; i++) {
        y = req[i][0] - 1;
        x = req[i][1] - 1;

        if (board[y][x] != 'O') {
            cout << 'X' << endl;
            continue;
        }

        string ans = "";

        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 8; k++) {
                if (board[j][k] == 'O') continue;

                int vx = x - k;
                int vy = y - j;

                if (board[j][k] == 'N') {
                    if ((abs(vx) == 1 && abs(vy) == 2) || (abs(vx) == 2 && abs(vy) == 1)) {
                        if (ans.find('N') == string::npos) {
                            ans += 'N';
                        }
                    }
                }

                if (board[j][k] == 'K') {
                    if ((abs(vx) == 1 && abs(vy) == 1) || (abs(vx) == 1 && abs(vy) == 0) || (abs(vx) == 0 && abs(vy) == 1)) {
                        if (ans.find('K') == string::npos) {
                            ans += 'K';
                        }
                    }
                }

                if (board[j][k] == 'P') {
                    if (vy == 1 && abs(vx) == 1) {
                        if (ans.find('P') == string::npos) {
                            ans += 'P';
                        }
                    }
                }

                if (board[j][k] == 'R') {
                    for (int d = 0; d < 4; d++) {
                        int nx = k + dx[d];
                        int ny = j + dy[d];

                        while (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
                            if (nx == x && ny == y) {
                                if (ans.find('R') == string::npos) {
                                    ans += 'R';
                                }
                                break;
                            }
                            nx += dx[d];
                            ny += dy[d];
                        }
                    }
                }

                if (board[j][k] == 'B') {
                    for (int d = 4; d < 8; d++) {
                        int nx = k + dx[d];
                        int ny = j + dy[d];

                        while (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
                            if (nx == x && ny == y) {
                                if (ans.find('B') == string::npos) {
                                    ans += 'B';
                                }
                                break;
                            }
                            nx += dx[d];
                            ny += dy[d];
                        }
                    }
                }

                if (board[j][k] == 'Q') {
                    for (int d = 0; d < 8; d++) {
                        int nx = k + dx[d];
                        int ny = j + dy[d];

                        while (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
                            if (nx == x && ny == y) {
                                if (ans.find('Q') == string::npos) {
                                    ans += 'Q';
                                }
                                break;
                            }
                            nx += dx[d];
                            ny += dy[d];
                        }
                    }
                }
            }
        }

        if (ans.empty()) {
            cout << 'O' << endl;
        } else {
            for (int j = 0; j < ans.size(); j++) {
                for (int k = 0; k < ans.size() - j - 1; k++) {
                    if (ans[k] > ans[k + 1]) {
                        char temp = ans[k];
                        ans[k] = ans[k + 1];
                        ans[k + 1] = temp;
                    }
                }
            }
            cout << ans << endl;
        }
    }

    return 0;
}
