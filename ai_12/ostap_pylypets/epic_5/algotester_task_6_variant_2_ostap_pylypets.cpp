#include <iostream>
using namespace std;

bool attacks(char piece, int i, int q, int x, int y) {
    int dx = x - i;
    int dy = y - q;
    //dx-зміщення по рядках вн- по стовпцях
    //знахлдимо відстанб
    int distanceX = dx < 0 ? -dx : dx;
    int distanceY = dy < 0 ? -dy : dy;
    //фігури ходять
    switch (piece) {
        case 'P':
            return dx == 1 && distanceY == 1;
        case 'R':
            return dx == 0 || dy == 0;
        case 'N':
            return (distanceX == 2 && distanceY == 1) ||
                   (distanceX == 1 && distanceY == 2);
        case 'B':
            return distanceX == distanceY;
        case 'K':
            return distanceX <= 1 && distanceY <= 1;
        case 'Q':
            return dx == 0 || dy == 0 || distanceX == distanceY;
        default:
            return false;
    }
}

int main() {
    int rowsCols = 8;
    char** chessBoard = new char*[rowsCols];
    //записуємо
    for (int i = 0; i < rowsCols; i++) {
        chessBoard[i] = new char[rowsCols];
        for (int q = 0; q < rowsCols; q++) {
            cin >> chessBoard[i][q];
        }
    }

    int Q;
    cin >> Q;

    const char pieceOrder[] = "BKNPQR";

    for (int query = 0; query < Q; query++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        //виключаємо пусті клітинки
        if (chessBoard[x][y] != 'O') {
            cout << "X\n";
            continue;
        }

        bool found[6] = {};
        //обходимо дошку
        for (int i = 0; i < rowsCols; i++) {
            for (int q = 0; q < rowsCols; q++) {
                char piece = chessBoard[i][q];
                //piece бере символ клітинки
                //перевіряємо чи фігура атакує
                if (attacks(piece, i, q, x, y)) {
                    for (int k = 0; k < 6; k++) {
                        //якщо фігура з pieceorder виводимо true
                        if (piece == pieceOrder[k]) {
                            found[k] = true;
                            break;
                        }
                    }
                }
            }
        }
        //виводимо атаковане
        bool hasAttack = false;
        for (int k = 0; k < 6; k++) {
            if (found[k]) {
                cout << pieceOrder[k];
                hasAttack = true;
            }
        }

        if (!hasAttack) {
            cout << 'O';
        }
        cout << '\n';
    }
    for (int i = 0; i < rowsCols; i++) {
        delete[] chessBoard[i];
    }
    delete[] chessBoard;
    return 0;
}