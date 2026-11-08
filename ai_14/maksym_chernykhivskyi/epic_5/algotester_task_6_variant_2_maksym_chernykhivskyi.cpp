/*Epic 5 - lab 6v2
Чернихівський Максим
Ші - 14*/

#include <iostream>

using namespace std;

void bishop(int i, int j, bool (&attacked_board)[8][8][6]){
    for (int k = 1; k < 8; k++){
        
        int att_i = i - k;
        int att_j = j - k;

        if (att_i >= 0 && att_i < 8 && att_j >= 0 && att_j < 8){
            attacked_board[att_i][att_j][0] = true;
        }
        int att_i2 = i + k;
        int att_j2 = j - k;

        if (att_i2 >= 0 && att_i2 < 8 && att_j2 >= 0 && att_j2 < 8){
            attacked_board[att_i2][att_j2][0] = true;
        }
        int att_i3 = i - k;
        int att_j3 = j + k;

        if (att_i3 >= 0 && att_i3 < 8 && att_j3 >= 0 && att_j3 < 8){
            attacked_board[att_i3][att_j3][0] = true;
        }
        int att_i4 = i + k;
        int att_j4 = j + k;

        if (att_i4 >= 0 && att_i4 < 8 && att_j4 >= 0 && att_j4 < 8){
            attacked_board[att_i4][att_j4][0] = true;
        }
    }
}

void king(int i, int j, bool (&attacked_board)[8][8][6]){
    for (int diff_i = -1; diff_i <= 1; diff_i++){
        for (int diff_j = -1; diff_j <= 1; diff_j++){

            if (diff_i == 0 && diff_j == 0){
                continue;
            }
            int att_i = i + diff_i;
            int att_j = j + diff_j;

            if (att_i >= 0 && att_i < 8 && att_j >= 0 && att_j < 8){
                attacked_board[att_i][att_j][1] = true;
            }
        }
    }
}

void knight(int i, int j, bool (&attacked_board)[8][8][6]){
    int diff_i[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int diff_j[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

    for (int k = 0; k < 8; k++){
        int att_i = i + diff_i[k];
        int att_j = j + diff_j[k];
        
        if (att_i >= 0 && att_i < 8 && att_j >= 0 && att_j < 8){
            attacked_board[att_i][att_j][2] = true;
        }
    }
}

void pawn(int i, int j, bool (&attacked_board)[8][8][6]){
    int att_i = i + 1;
    for (int k = -1; k <= 1; k++){
        if (k == 0) {
            continue;
        }
        int att_j = j + k;

        if (att_i >= 0 && att_i < 8 && att_j >= 0 && att_j < 8){
            attacked_board[att_i][att_j][3] = true;
        }
    }
}

void queen(int i, int j, bool (&attacked_board)[8][8][6]){
    for (int k = 1; k < 8; k++){
        
        int att_i = i - k;
        int att_j = j - k;

        if (att_i >= 0 && att_i < 8 && att_j >= 0 && att_j < 8){
            attacked_board[att_i][att_j][4] = true;
        }
        int att_i2 = i + k;
        int att_j2 = j - k;

        if (att_i2 >= 0 && att_i2 < 8 && att_j2 >= 0 && att_j2 < 8){
            attacked_board[att_i2][att_j2][4] = true;
        }
        int att_i3 = i - k;
        int att_j3 = j + k;

        if (att_i3 >= 0 && att_i3 < 8 && att_j3 >= 0 && att_j3 < 8){
            attacked_board[att_i3][att_j3][4] = true;
        }
        int att_i4 = i + k;
        int att_j4 = j + k;

        if (att_i4 >= 0 && att_i4 < 8 && att_j4 >= 0 && att_j4 < 8){
            attacked_board[att_i4][att_j4][4] = true;
        }
    } 
        
    for (int k = 0; k < 8; k++){
        if (k == j){
            continue;
        }
        attacked_board[i][k][4] = true;
    }    
    
    for (int k = 0; k < 8; k++){
        if (k == i){
            continue;
        }
        attacked_board[k][j][4] = true;
    }
}

void rook(int i, int j, bool (&attacked_board)[8][8][6]){
    for (int k = 0; k < 8; k++){
        if (k == j){
            continue;
        }
        attacked_board[i][k][5] = true;
    }    
    
    for (int k = 0; k < 8; k++){
        if (k == i){
            continue;
        }
        attacked_board[k][j][5] = true;
    }
}


int main(){
    char board[8][8];
    bool attacked_board[8][8][6] = {false};


    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            cin >> board[i][j];
        }
    }

    int Q;
    cin >> Q;

    for (int i = 0; i < 8; i++){
         for (int j = 0; j < 8; j++){
            char current = board[i][j];
            switch (current) {
                case 'B': // Слон
                    bishop(i, j, attacked_board);
                    break;
                case 'K': // Король
                    king(i, j, attacked_board);
                    break;
                case 'N': // Кінь
                    knight(i, j, attacked_board);
                    break;
                case 'P': // Пішак
                    pawn(i, j, attacked_board);
                    break;
                case 'Q': // Королева
                    queen(i, j, attacked_board);
                    break;
                case 'R': // Тура
                    rook(i, j, attacked_board);
                    break;
            }
        }
    }
    for (int i = 0; i < Q; i++){
        int x, y;
        cin >> x >> y;
        x--;
        y--;    

        if (board[x][y] != 'O') {
            cout << "X" << endl;
            continue;
        }

        string result = "";

        char figures[6] = {'B', 'K', 'N', 'P', 'Q', 'R'};

        for (int k = 0; k < 6; k++){
            if (attacked_board[x][y][k] == true){
                result += figures[k];
            }
        }

        if (result == ""){
            cout << "O" << endl;
        } else {
            cout << result << endl;
        }
    }
}
