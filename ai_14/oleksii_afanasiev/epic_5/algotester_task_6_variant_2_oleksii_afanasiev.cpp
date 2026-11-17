/*
Задача: Lab 6v2
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>

using namespace std;

void bubbleSort(char* arr, int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                char t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
}

bool checkAttack(int x, int y, char piece, int x_p, int y_p)
{
    switch(piece)
    {
        case 'P':
            return x - x_p == 1 && abs(y - y_p) == 1;
        case 'B':
            return abs(x - x_p) == abs(y - y_p);
        case 'N':
            return (abs(x - x_p) == 2 && abs(y - y_p) == 1) || (abs(x - x_p) == 1 && abs(y - y_p) == 2);
        case 'R':
            return (x - x_p == 0) || (y - y_p == 0);
        case 'Q':
            return (x - x_p == 0) || (y - y_p == 0) || (abs(x - x_p) == abs(y - y_p)); 
        case 'K':
            return (abs(x - x_p) <= 1) && (abs(y - y_p) <= 1);
        default:
            return false;
    }
}

int main()
{
    char board[8][9];
    int Q;

    for(int i = 0; i < 8; i++)
    {
        cin >> board[i];
    }

    cin >> Q;
    
    for(int i = 0; i < Q; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;

        if(board[x][y] != 'O')
        {
            cout << "X" << endl;
            continue;
        }

        char attackers[64];
        int count = 0;

        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(checkAttack(x, y, board[i][j], i, j))
                {
                    attackers[count] = board[i][j];
                    count++;
                }
            }
        }

        bubbleSort(attackers, count);

        if(count == 0) cout << "O";
        else
        {
            for(int i = 0; i < count; i++)
            {
                if(i == 0 || attackers[i] != attackers[i - 1])
                {
                    cout << attackers[i];
                }
            }
        }

        cout << endl;
    }

    return 0;
}
