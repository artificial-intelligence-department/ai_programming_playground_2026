#include <algorithm>
#include <iostream>

using namespace std;

void userInput(int& n)
{
    while (!(cin >> n) || n <= 0 || n >= 100)
    {
        cout << "Введіть число з проміжку (0, 100)" << '\n';
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

bool findMinUnique(int** matrix, int r, int c, int& unique_min_el)
{
    int* new_array = new int[r * c];
    int k = 0;

    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            new_array[k++] = matrix[i][j];
        }
    }

    sort(new_array, new_array + r * c);

    bool found = false;
    for (int el = 0; el < r * c; ++el)
    {
        bool l_same = (el > 0) && (new_array[el] == new_array[el - 1]);
        bool r_same = (el < r * c - 1) && (new_array[el] == new_array[el + 1]);
        if (!l_same && !r_same)
        {
            found = true;
            unique_min_el = new_array[el];
            break;
        }
    }

    delete[] new_array;
    return found;
}

int main()
{
    int r, c;
    cout << "Введіть кількість рядків: ";
    userInput(r);
    cout << "Введіть кількість стовпців: ";
    userInput(c);

    int** matrix = new int*[r];
    for (int i = 0; i < r; ++i) matrix[i] = new int[c];

    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            while (!(cin >> matrix[i][j]))
            {
                cout << "Введіть число" << '\n';
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
    }

    int unique_min_el;
    if (findMinUnique(matrix, r, c, unique_min_el))
    {
        cout << endl << "Мінімальний неповторюваний елемент: " << unique_min_el << endl;
    }
    else
    {
        cout << endl << "Усі елементи повторюються." << endl;
    }

    for (int i = 0; i < r; ++i) delete[] matrix[i];
    delete[] matrix;

    return 0;
}