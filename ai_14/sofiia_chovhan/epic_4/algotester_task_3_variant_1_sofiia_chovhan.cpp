/*Sofiia Chovhan 
AI 14
Algotester Lab 3 Variant 1*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
    int linesCount;
    cin >> linesCount;
    cin.ignore();

    string spellLine;
    int rituals = 0;

    for (int i = 0; i < linesCount; i++)
    {
        getline(cin, spellLine);
        char previous = ' ';

        for (char symbol : spellLine)
        {
            if (symbol == '#' && previous != '#')
            {
                rituals++;
            }
            previous = symbol;
        }
    }

    cout << rituals << endl;
    return 0;
}
