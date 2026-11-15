#include <iostream>

using namespace std;
bool isAttackedByBishop(int i, int j,int x, int y);
bool isAttackedByKnight(int i, int j,int x, int y);
bool isAttackedByKing(int i, int j,int x, int y);
bool isAttackedByPawn(int i, int j,int x, int y);
bool isAttackedByTheRook(int i, int j,int x, int y);
int checkCoords(int x,int y, char board[][8]);
int main(){
    char board[8][8]={'0'};
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cin>>board[i][j];
        }
        
    }
    int length;
cin >> length;

int** coords = new int*[length];
for (int i = 0; i < length; i++) {
    coords[i] = new int[2];
}

// Зчитуємо пару координат (x, y) для кожного i
for (int i = 0; i < length; i++) {
    cin >> coords[i][0] >> coords[i][1];
}

for (int i = 0; i < length; i++) {
    checkCoords(coords[i][0]-1, coords[i][1]-1, board);
}

for (int i = 0; i < length; i++) {
    delete[] coords[i];
}
delete[] coords;
    
    

    
    
}
bool isAttackedByBishop(int i, int j,int x, int y){
    int dynamic_row=i;
    int dynamic_col=j;
    while(dynamic_row>=0 && dynamic_col>=0 && dynamic_col<8 && dynamic_row<8){
        if(x==dynamic_row && y==dynamic_col){
            return 1;
        }
        dynamic_col-=1;
        dynamic_row-=1;
    }
    dynamic_row=i;
    dynamic_col=j;
    while(dynamic_row>=0 && dynamic_col>=0 && dynamic_col<8 && dynamic_row<8){
        if(x==dynamic_row && y==dynamic_col){
            return 1;
        }
        dynamic_col+=1;
        dynamic_row+=1;
    }
    dynamic_row=i;
    dynamic_col=j;
    while(dynamic_row>=0 && dynamic_col>=0 && dynamic_col<8 && dynamic_row<8){
        if(x==dynamic_row && y==dynamic_col){
            return 1;
        }
        dynamic_col+=1;
        dynamic_row-=1;
    }
    dynamic_row=i;
    dynamic_col=j;
    while(dynamic_row>=0 && dynamic_col>=0 && dynamic_col<8 && dynamic_row<8){
        if(x==dynamic_row && y==dynamic_col){
            return 1;
        }
        dynamic_col-=1;
        dynamic_row+=1;
    }
    return 0;
}
bool isAttackedByKing(int i, int j,int x, int y){
    for(int k=-1; k<2;k++){
        for(int m=-1;m<2;m++){
            if(x==i+k&&y==j+m){
                return 1;
            }
        }
    }
    return 0;
}
bool isAttackedByKnight(int i, int j, int x, int y) {
    int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
    int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};

    for (int k = 0; k < 8; k++) {
        if (x == i + dx[k] && y == j + dy[k]) {
            return true;
        }
    }
    return false;
}
bool isAttackedByPawn(int i, int j, int x, int y) {
    if (x == i + 1 && (y == j - 1 || y == j + 1)) {
        return true;
    }
    return false;
}
bool isAttackedByTheRook(int i, int j,int x, int y){
    for(int i = 0;i<8;i++){
        if(x==i && y == j){
            return 1;
        }
    }
    for(int j = 0;j<8;j ++){
        if(x==i && y == j){
            return 1;
        }
    }
    return 0;
}


int checkCoords(int x,int y, char board[][8]){
    if (board[x][y] != 'O' && board[x][y] != '0') {
        cout << 'X' << endl;
        return 0;
    }

    bool bishop_check = false;
    bool king_check = false;
    bool knight_check = false;
    bool pawn_check = false;
    bool queen_check = false;
    bool rook_check = false;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (board[i][j]) {
            case 'B':
                if (isAttackedByBishop(i, j, x, y)) bishop_check = true;
                break;
            case 'K':
                if (isAttackedByKing(i, j, x, y)) king_check = true;
                break;
            case 'N':
                if (isAttackedByKnight(i, j, x, y)) knight_check = true;
                break;
            case 'P':
                if (isAttackedByPawn(i, j, x, y)) pawn_check = true;
                break;
            case 'Q':
                if (isAttackedByTheRook(i, j, x, y) || isAttackedByBishop(i, j, x, y)) queen_check = true;
                break;
            case 'R':
                if (isAttackedByTheRook(i, j, x, y)) rook_check = true;
                break;
            }
        }
    }

    bool is_there_something = false;

    if (bishop_check) { cout << 'B'; is_there_something = true; }
    if (king_check)   { cout << 'K'; is_there_something = true; }
    if (knight_check) { cout << 'N'; is_there_something = true; }
    if (pawn_check)   { cout << 'P'; is_there_something = true; }
    if (queen_check)  { cout << 'Q'; is_there_something = true; }
    if (rook_check)   { cout << 'R'; is_there_something = true; }

    if (!is_there_something) {
        cout << 'O';
    }
    cout << endl;
    return 0;
}