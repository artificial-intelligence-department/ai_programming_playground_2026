/*Sofiia Chovhan 
AI 14
Lab 4 Variant 21*/
#include <iostream>
using namespace std;

void showRing(const int* values, int count, int start, int direction)
{
    int position = start;

    for (int step = 0; step < count; step++)
    {
        cout << values[position];
        if (step + 1 < count)
        {
            cout << ' ';
        }
        position = (position + direction + count) % count;
    }
    cout << endl;
}

int main()
{
    int length;
    cout << "Enter the number of elements (at least 3): ";
    if (!(cin >> length) || length < 3)
    {
        cout << "Invalid number of elements." << endl;
        return 1;
    }

    int* circle = new int[length];
    cout << "Enter the elements: ";
    for (int place = 0; place < length; place++)
    {
        if (!(cin >> circle[place]))
        {
            cout << "Invalid element." << endl;
            delete[] circle;
            return 1;
        }
    }

    int k;
    cout << "Enter K (from 1 to " << length << "): ";
    if (!(cin >> k) || k < 1 || k > length)
    {
        cout << "Invalid K." << endl;
        delete[] circle;
        return 1;
    }

    cout << "Ring to the left from K: ";
    showRing(circle, length, k - 1, -1);

    int newLength = length + 4;
    int* updated = new int[newLength];

    for (int place = 0; place < length; place++)
    {
        updated[place] = circle[place];
    }

    updated[length] = circle[0];

    for (int offset = 0; offset < 3; offset++)
    {
        updated[length + 1 + offset] = circle[length - 3 + offset];
    }

    delete[] circle;
    circle = updated;
    length = newLength;

    cout << "Ring to the right from K after adding elements: ";
    showRing(circle, length, k - 1, 1);

    delete[] circle;
    return 0;
}
