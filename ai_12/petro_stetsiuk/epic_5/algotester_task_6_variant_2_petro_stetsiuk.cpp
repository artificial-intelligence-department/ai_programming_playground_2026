/*
Algotester lab 6
Варіант: 2
Автор: Петро Стецюк
Група: ШІ-12
*/
#include <iostream>
#include <string>


using namespace std;

void checkCell(char a[9][9], string s[65], int x, int y, int q)
{
    
    if (a[x][y] != 'O') {
        s[q] = "X";
        return;
    }

    bool hasB = false, hasK = false, hasN = false, hasP = false, hasQ = false, hasR = false;

    
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            char fig = a[i][j];
            if (fig == 'O') continue;

            int dx = abs(x - i); 
            int dy = abs(y - j); 

            if (fig == 'P') {
                
                if (i == x - 1 && dy == 1) {
                    hasP = true;
                }
            }
            else if (fig == 'R') {
                
                if (i == x || j == y) {
                    hasR = true;
                }
            }
            else if (fig == 'B') {
                
                if (dx == dy) {
                    hasB = true;
                }
            }
            else if (fig == 'Q') {
                
                if (i == x || j == y || dx == dy) {
                    hasQ = true;
                }
            }
            else if (fig == 'N') {
                
                if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
                    hasN = true;
                }
            }
            else if (fig == 'K') {
                
                if (dx <= 1 && dy <= 1) {
                    hasK = true;
                }
            }
        }
    }

    
    s[q] = "";
    if (hasB) s[q] += 'B';
    if (hasK) s[q] += 'K';
    if (hasN) s[q] += 'N';
    if (hasP) s[q] += 'P';
    if (hasQ) s[q] += 'Q';
    if (hasR) s[q] += 'R';

    if (s[q] == "") {
        s[q] = "O";
    }
}
int main()
{
    const int n=8;
    string s[65];
    char a[9][9];
    int i,j,q,x,y;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        cin>>a[i][j];
    }
    cin>>q;
    for(i=0;i<q;i++)
    {
        cin>>x>>y;
        checkCell(a, s, x, y, i);
    }
    for (i = 0; i < q; i++) 
    {
        cout << s[i] <<endl;
    }

}