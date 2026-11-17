#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cmath>
#include <algorithm>

using namespace std;

bool attacks(char type, int fr, int fc, int tr, int tc){
    int dr = tr - fr;  
    int dc = tc - fc;   
    if (dr == 0 && dc == 0) return false;

    switch (type){
        case 'P':  
            return dr == 1 && (dc == 1 || dc == -1);
        case 'R':   
            return dr == 0 || dc == 0;
        case 'B':   
            return abs(dr) == abs(dc);
        case 'Q':   
            return dr == 0 || dc == 0 || abs(dr) == abs(dc);
        case 'N':   
            return (abs(dr) == 1 && abs(dc) == 2) ||
                   (abs(dr) == 2 && abs(dc) == 1);
        case 'K':  
            return abs(dr) <= 1 && abs(dc) <= 1;

        default:
            return false;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> board(8);
    for (int i = 0; i < 8; i++)
        cin >> board[i];
    int Q;
    cin >> Q;
    while (Q--){
        int x, y;
        cin >> x >> y;
        int tr = x - 1;
        int tc = y - 1;
        if (board[tr][tc] != 'O'){
            cout << "X\n";
            continue;
        }
        set<char> attackers;
        for (int r = 0; r < 8; r++){
            for (int c = 0; c < 8; c++){
                char p = board[r][c];
                if (p != 'O' && attacks(p, r, c, tr, tc))
                    attackers.insert(p);
            }
        }
        if (attackers.empty()){
            cout << "O\n";                 
        }else{
            for (char ch : attackers) cout << ch;
            cout << "\n";
        }
    }
    return 0;
}
