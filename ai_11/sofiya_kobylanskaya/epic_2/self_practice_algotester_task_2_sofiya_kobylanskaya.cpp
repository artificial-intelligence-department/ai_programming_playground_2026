
#include <iostream>
using namespace std;

int l[100001];
int r[100001];
int c[100001];

int nextCell[100002];
int cellColor[100001];

int findNext(int cell)
{
    if (nextCell[cell] == cell)
    {
        return cell;
    }

    nextCell[cell] = findNext(nextCell[cell]);
    return nextCell[cell];
}

int main()
{
    int n, m;
    cin >> n >> m;

    for (int action = 1; action <= m; action++)
    {
        cin >> l[action] >> r[action] >> c[action];
    }

    for (int cell = 1; cell <= n + 1; cell++)
    {
        nextCell[cell] = cell;
    }

    for (int action = m; action >= 1; action--)
    {
        int cell = findNext(l[action]);

        while (cell <= r[action])
        {
            cellColor[cell] = c[action];

            nextCell[cell] = findNext(cell + 1);

            cell = findNext(cell);
        }
    }

    for (int cell = 1; cell <= n; cell++)
    {
        cout << cellColor[cell] << " ";
    }

    cout << endl;

    return 0;
}