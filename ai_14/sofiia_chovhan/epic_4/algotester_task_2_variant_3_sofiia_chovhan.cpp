/*Sofiia Chovhan
AI 14 
Algotester Lab 2 Variant 3*/

#include <iostream>
using namespace std;

int main()
{
    int size;
    cin >> size;

    int* cells = new int[size + 1];

    for (int i = 1; i <= size; i++)
    {
        cin >> cells[i];
    }

    int west = 1;
    int east = size;

    while (west + 1 < east)
    {
        int nextWest = west + cells[west];
        int nextEast = east - cells[east];

        west = nextWest;
        east = nextEast;
    }

    cout << west << " " << east << endl;

    if (west == east)
    {
        cout << "Collision" << endl;
    }
    else if (west > east)
    {
        cout << "Miss" << endl;
    }
    else
    {
        cout << "Stopped" << endl;
    }

    delete[] cells;

    return 0;
}
