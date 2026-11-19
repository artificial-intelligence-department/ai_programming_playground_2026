#include <iostream>
#include <cstring>
using namespace std;
const int MAX_N = 9;
const int MAX_Q = 1000;
int main()
{
    int n;
    cin >> n;
    char sudoku[MAX_N][MAX_N + 1];
    for (int i = 0; i < n ; i++)
    {
        cin >> sudoku[i];
    }
    int q;
    cin >> q;
    int vectors[MAX_Q][2];
    for (int i = 0; i < q; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cin >> vectors[i][j];
        }
    }
    for (int i = 0; i < q; i++)
    {
        int x = vectors[i][0];
        int y = vectors[i][1];
        int r = x -1;
        int c = y -1;
        if(i >0 ){
            cout << endl;
        }
        if(sudoku[r][c] != '0'){
            cout << 1 << endl;
            cout << sudoku[r][c] << endl;
            continue;
        }
        int digits[9];
        int countOfDigits = 0;
        for (int d = 1; d <= n; d++)
        {
            char digit ='0' + d;
            bool isFree = true;
            for (int k = 0; k < n; k++)
            {
                if(sudoku[r][k] == digit || sudoku[k][c] == digit){
                    isFree = false;
                    break;
                }
            }
            if(isFree){
                digits[countOfDigits] = d;
                countOfDigits++;
            }
            
        }
         cout << countOfDigits << endl;
        for (int k = 0; k < countOfDigits; k++)
        {
            cout << digits[k];
            if(k < countOfDigits - 1){
                cout << " ";
            }
        }
        if(countOfDigits > 0){
            cout << endl;
        }
    }
}
    
