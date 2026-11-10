#include <iostream>
#include <vector>
#include <cmath>  
#include <algorithm> 

using namespace std;

string checkCell(vector<string> board, int targetX, int targetY) {
    if (board[targetX][targetY] != 'O') {
        return "X";
    }
    
    string attackers = "";
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            char piece = board[i][j];
            if (piece == 'O') continue;
            
            if (piece == 'P') {
                if (targetX == i+1 && (targetY == j-1 || targetY == j+1)) attackers += 'P';
            } 
            
            if (piece == 'R') {
                if (targetX == i || targetY == j) attackers += 'R';
            }
            
            if (piece == 'N') {
                int dx = abs(i-targetX);
                int dy = abs(j-targetY);
                if ((dx == 1 && dy == 2) || (dx == 2 && dy ==1)) attackers += 'N';
            }
            
            if (piece == 'B') {
                int dx = abs(i-targetX);
                int dy = abs(j-targetY);
                if (dx == dy) attackers += 'B';
            }
            
            if (piece == 'K') {
                int dx = abs(i-targetX);
                int dy = abs(j-targetY);
                if ((dx == 1 && dy == 1) || (dx == 0 && dy == 1) || (dx == 1 && dy == 0)) attackers += 'K';
            }
            
            if (piece == 'Q') {
                int dx = abs(i-targetX);
                int dy = abs(j-targetY);
                if (targetX == i || targetY == j || (dx == dy)) attackers += 'Q';
            }
            
        }
    }
    
    if (attackers.empty()) {
        return "O";
    }
    
    sort(attackers.begin(), attackers.end());
    attackers.erase(unique(attackers.begin(), attackers.end()), attackers.end());
    return attackers;
}

int main() {
    vector<string> board(8); 
    for (int i = 0; i < 8; i++) {
        cin >> board[i];
    }
    
    int Q;
    cin >> Q;
    
    for (int i = 0; i < Q; i++) {
        int x, y;
        cin >> x >> y;
        cout << checkCell(board, x - 1, y - 1) << endl;
    }
    
    return 0;
}