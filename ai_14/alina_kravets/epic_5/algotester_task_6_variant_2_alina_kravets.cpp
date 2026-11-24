/*Алготестер lab6v2
ШІ-14
Кравець Аліна*/
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

void sortByAlphabet(string &s, int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - 1 - i; j++)
        {
            if (s[j] > s[j + 1])
            {
                swap(s[j], s[j + 1]);
            }
        }
    }
}

string findAttackers(char chess[8][9], int x, int y)
{
    bool attackedByPawn = false;
    bool attackedByRook = false;
    bool attackedByKnight = false;
    bool attackedByBishop = false;
    bool attackedByKing = false;
    bool attackedByQueen = false;
    string attackers = "";

    if (chess[x][y] != 'O') return "X";
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int dist_x = fabs(x - i);
            int dist_y = fabs(y - j);
            if (chess[i][j] == 'O') continue;
            else if ((chess[i][j] == 'P') && !attackedByPawn && i == x - 1 && ((j == y + 1) || (j == y - 1))) 
            {
                attackers += 'P';
                attackedByPawn = true;
            }
            else if ((chess[i][j] == 'R') && !attackedByRook && ((i == x) || (j == y)))
            {
                attackers += 'R';
                attackedByRook = true;
            } 
            else if ((chess[i][j] == 'N') && !attackedByKnight && ((dist_x == 1 && dist_y == 2) || (dist_x == 2 && dist_y == 1)))
            {
                attackers += 'N';
                attackedByKnight = true;
            } 
            else if ((chess[i][j] == 'B') && !attackedByBishop && (dist_x == dist_y))
            {
                attackers += 'B';
                attackedByBishop = true;
            } 
            else if ((chess[i][j] == 'K') && !attackedByKing && ((dist_x == 1 && dist_y == 1) || ((dist_x == 0 && dist_y == 1)) || (dist_x == 1 && dist_y == 0)))
            {
                attackers += 'K';
                attackedByKing = true;
            } 
            else if ((chess[i][j] == 'Q') && !attackedByQueen && (i == x || j == y || (dist_x == dist_y)))
            {
                attackers += 'Q';
                attackedByQueen = true;
            } 
        }
    }

    int len = attackers.length();

    if(len == 0) return "O";
    sortByAlphabet(attackers, len);
    return attackers;
}

int main()
{
    char chess[8][9] = {'\0'};
    int q = 0;
    int x = 0;
    int y = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cin >> chess[i][j];
        }
    }

    cin >> q;
    for(int i = 0; i < q; i++)
    {
        cin >> x >> y;

        cout << findAttackers(chess, x - 1, y - 1) << endl;
    }

    return 0;
}
