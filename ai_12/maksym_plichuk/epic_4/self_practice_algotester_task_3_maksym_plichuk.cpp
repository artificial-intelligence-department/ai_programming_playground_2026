#include <iostream>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    bool *rowHasVirus = new bool[n]();
    bool *colHasVirus = new bool[m]();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            char num;
            cin >> num;
            if (num=='1') {
                rowHasVirus[i] = true;
                colHasVirus[j] = true;
            }
        }
    }

    bool allRowsHaveVirus = true;
    for (int i = 0; i < n; i++)
    {
        if (!rowHasVirus[i])
        {
            allRowsHaveVirus = false;
            break;
        }
    }

    bool allColsHaveVirus = true;
    for (int j = 0; j < m; j++)
    {
        if (!colHasVirus[j])
        {
            allColsHaveVirus = false;
            break;
        }
    }

    if (allRowsHaveVirus || allColsHaveVirus) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }

    delete[] rowHasVirus;
    delete[] colHasVirus;
    return 0;
}