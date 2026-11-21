#include<cstdio>
#include<algorithm>
#include<string>
using namespace std;

int main(){
    int rows = 8;
    char ** desk = new char*[rows];
    for(int i = 0; i < rows; i++){
        desk[i] = new char[rows+1];
        scanf("%s", desk[i]);
    }
    int nOfAttacks = 0;
    scanf("%d", &nOfAttacks); 
    while(nOfAttacks > 0){
        int tmpX = 0;
        int tmpY = 0;
        scanf("%d %d", &tmpX, &tmpY);
        tmpX --;
        tmpY --;
        if (desk[tmpX][tmpY] != 'O') {
            printf("X\n");
            nOfAttacks--;
            continue;
        }
        string ans;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < rows; j++) {
                if (i == tmpX && j == tmpY) continue;

                int dtmpX = i - tmpX;
                int dtmpY = j - tmpY;

                switch (desk[i][j]) {
                    case 'P':
                        if (i == tmpX - 1 && abs(dtmpY) == 1) ans += 'P';
                        break;
                    case 'R':
                        if (i == tmpX || j == tmpY) ans += 'R';
                        break;
                    case 'N':
                        if ((abs(dtmpX) == 1 && abs(dtmpY) == 2) || (abs(dtmpX) == 2 && abs(dtmpY) == 1))
                            ans += 'N';
                        break;
                    case 'B':
                        if (abs(dtmpX) == abs(dtmpY)) ans += 'B';
                        break;
                    case 'K':
                        if (abs(dtmpX) <= 1 && abs(dtmpY) <= 1) ans += 'K';
                        break;
                    case 'Q':
                        if (i == tmpX || j == tmpY || abs(dtmpX) == abs(dtmpY)) ans += 'Q';
                        break;
                }
            }
        }
        if (ans.empty()) {
            printf("O\n");
        } else {
            sort(ans.begin(), ans.end());
            ans.erase(unique(ans.begin(), ans.end()), ans.end());
            printf("%s\n", ans.c_str());
        }
        nOfAttacks--;
    }
     for(int i = 0; i < rows; i++){
        delete[] desk[i];
    }
    delete[] desk;
    desk = nullptr;
}