/*
Задача: Замовлення від квітникарів (Algotester)
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_ROWS = 100;
const int MAX_COLS = 100;

int main() {

        int M[MAX_ROWS][MAX_COLS];
        int rowsSum[MAX_ROWS];
        int colsSum[MAX_COLS];
        int m,n;

        cin >> n >> m;

        for(int i = 0; i< n; i++)
        {
            rowsSum[i] = 0;
        }

        for(int j = 0; j< m; j++)
        {
            colsSum[j] = 0;
        }

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                cin >> M[i][j];
            }
        }

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                rowsSum[i] += M[i][j];
                colsSum[j] += M[i][j];
            }
        }

        int max = 0;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(rowsSum[i] + colsSum[j] - M[i][j] > max) max = rowsSum[i] + colsSum[j] - M[i][j];
            }
        }

        cout << max;

        return 0;
    }
