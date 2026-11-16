#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main(){
    string board[8];
    for(int i = 0; i < 8; i++) cin >> board[i];

    int q;
    cin >> q;

    while(q--){
        int x, y;
        cin >> x >> y;
        x--; y--;
        if(board[x][y] != 'O'){
            cout << "X\n";
            continue;
        }

        string result = "";

        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                char f = board[i][j];

                // a - скільки рядків між фігурами, b - скільки стовпців
                int a = abs(x - i), b = abs(y - j);

                if(f == 'P' && x - i == 1 && b == 1) result += f;
                if(f == 'R' && (a == 0 || b == 0)) result += f;
                if(f == 'N' && a*b == 2) result += f;
                if(f == 'B' && a == b) result += f;
                if(f == 'K' && a <= 1 && b <= 1) result += f;
                if(f == 'Q' && (a == 0 || b == 0 || a == b)) result += f;
            }
        }
        if(result.empty()) cout << "O\n";
        else{
            sort(result.begin(), result.end());
            for(int k = 0; k < result.size(); k++){
                if(k == 0 || result[k] != result[k-1])
                    cout << result[k];
            }
            cout << "\n";
        }
    }

    return 0;
}