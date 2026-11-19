/*Задача 0484 - "Патріотична cтрічка"
Максімко Павло - СШІ-13*/

#include <iostream>

using namespace std;

const int MAX_LENGTH = 100000;

int main()
{
    char ribbon_colors[MAX_LENGTH + 1];
    cin >> ribbon_colors;

    int changes_start_B = 0;
    int changes_start_Y = 0;

    for(int i = 0; ribbon_colors[i] != '\0'; i++)
    {
        char expected_B = (i % 2 == 0) ? 'B' : 'Y';
        char expected_Y = (i % 2 == 0) ? 'Y' : 'B';

        if(ribbon_colors[i] != expected_B)
        {
            changes_start_B++;
        }

        if(ribbon_colors[i] != expected_Y)
        {
            changes_start_Y++;
        }
    }

    if(changes_start_B <= changes_start_Y) cout << changes_start_B << endl;
    else cout << changes_start_Y << endl;

    return 0;
}