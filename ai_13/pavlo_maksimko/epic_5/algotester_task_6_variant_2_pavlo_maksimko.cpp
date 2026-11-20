/*Алготестер задача 6 варіант 2
Максімко Павло - СШІ-13*/

#include <iostream>

using namespace std;

const int ROWS = 8;
const int COLS = 8;

const int DIRECTIONS = 8;

bool figureOnBoard(int x, int y);
void merge(char *attackers, int left, int right, int mid);
void sortAttackers(char *attackers, int left, int right);

int main()
{
    char board[ROWS][COLS + 1];
    char attackers[ROWS * COLS];
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            cin >> board[i][j];
        }
        board[i][COLS] = '\0';
    }

    int horizonX[DIRECTIONS / 2] = {1, -1, 0, 0};
    int horizonY[DIRECTIONS / 2] = {0, 0, -1, 1};

    int diagX[DIRECTIONS / 2] = {-1, -1, 1, 1};
    int diagY[DIRECTIONS / 2] = {-1, 1, -1, 1};

    int knightX[DIRECTIONS] = {2, -2, 2, -2, 1, -1, 1, -1};
    int knightY[DIRECTIONS] = {1, 1, -1, -1, 2, 2, -2, -2}; 

    int Q;
    cin >> Q;
    int x, y;
    for(int i = 0; i < Q; i++)
    {
        int k = 0;
        cin >> y >> x;
        if(board[y - 1][x - 1] != 'O')
        {
            cout << "X" << endl;
            continue;
        }

        for(int j = 0; j < DIRECTIONS / 2; j++)
        {
            for(int step = 1; step <= DIRECTIONS; step++)
            {
                int step_x = x - 1 + step * horizonX[j];
                int step_y = y - 1 + step * horizonY[j];

                if(!figureOnBoard(step_x, step_y)) break;
                
                if(board[step_y][step_x] == 'R' || board[step_y][step_x] == 'Q' || (step == 1 && board[step_y][step_x] == 'K'))
                {
                    attackers[k] = board[step_y][step_x];
                    k++;
                }
            }
        }

        for(int j = 0; j < DIRECTIONS / 2; j++)
        {
            for(int step = 1; step <= DIRECTIONS; step++)
            {
                int step_x = x - 1 + step * diagX[j];
                int step_y = y - 1 + step * diagY[j];

                if(!figureOnBoard(step_x, step_y)) break;
                
                if(board[step_y][step_x] == 'B' || board[step_y][step_x] == 'Q' || (step == 1 && board[step_y][step_x] == 'K'))
                {
                    attackers[k] = board[step_y][step_x];
                    k++;
                }
                if(step == 1 && diagY[j] == -1 && board[step_y][step_x] == 'P')
                {
                    attackers[k] = board[step_y][step_x];
                    k++;
                }
            }
        }

        for(int j = 0; j < DIRECTIONS; j++)
        {
            int step_x = x - 1 + knightX[j];
            int step_y = y - 1 + knightY[j];
                
            if(figureOnBoard(step_x, step_y) && board[step_y][step_x] == 'N')
            {
                attackers[k] = board[step_y][step_x];
                k++;
            }
        }

        if(k == 0)
        {
            cout << "O" << endl;
        }
        else
        {
            sortAttackers(attackers, 0, k - 1);
            cout << attackers[0];
            for(int j = 1; j < k; j++)
            {
                if(attackers[j] != attackers[j - 1]) cout << attackers[j];
            }
            cout << endl;
        }
    }
    return 0;
}

bool figureOnBoard(int x, int y)
{
    return (x >= 0 && x < COLS && y < ROWS && y >= 0);
}

void merge(char *attackers, int left, int right, int mid)
{
    int i = left;
    int j = mid + 1;
    int k = 0;
    char t[ROWS * COLS];

    while(i <= mid && j <= right)
    {
        if(attackers[i] <= attackers[j])
        {
            t[k] = attackers[i];
            k++; i++;
        }
        else 
        {
            t[k] = attackers[j];
            k++; j++;
        }
    }

    while(i <= mid)
    {
        t[k] = attackers[i];
        k++; i++;
    }

    while(j <= right)
    {
        t[k] = attackers[j];
        k++; j++;
    }

    for(int p = 0; p < k; p++)
    {
        attackers[p + left] = t[p];
    }
}

void sortAttackers(char *attackers, int left, int right)
{
    if(left >= right) return;

    int mid = left + (right - left) / 2;

    sortAttackers(attackers, left, mid);
    sortAttackers(attackers, mid + 1, right);
    merge(attackers, left, right, mid);
}