/*
    Задача: Зеник-садівник
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
using namespace std;
int main() {
    int rows, cols;
    cin >> rows >> cols;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if ((i + j / 2)%2 == 0)
            {
                cout << 'x';
            }
            else 
            {
                cout << 'o';
            }
        }
        cout << endl;
    }
    return 0;
}
