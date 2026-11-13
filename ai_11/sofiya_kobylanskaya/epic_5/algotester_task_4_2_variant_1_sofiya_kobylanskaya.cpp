#include <iostream>
using namespace std;

int main()
{
    int n[100];
    int m[100];
    int N;
    int M;

    cin >> N;
    if (N < 1 || N > 100)
    {
        return 0;
    }
    for (int i = 0; i < N; i++)
    {
        cin >> n[i];
        if (n[i] < 1 || n[i] > 100)
        {
            return 0;
        }
    }

    cin >> M;
    if (M < 1 || M > 100)
    {
        return 0;
    }
    for (int i = 0; i < M; i++)
    {
        cin >> m[i];
        if (m[i] < 1 || m[i] > 100)
        {
            return 0;
        }
    }

    int countN = 0;
    int differenceN[100];
    bool usedM[100] = {false};

    for (int i = 0; i < N; i++)
    {
        bool found = false;
        for (int j = 0; j < M; j++)
        {
            if (n[i] == m[j] && !usedM[j])
            {
                found = true;
                usedM[j] = true;
                break;
            }
        }
        if (!found)
        {
            differenceN[countN] = n[i];
            countN++;
        }
    }
    for (int i = 0; i < countN - 1; i++)
    {
        for (int j = 0; j < countN - i - 1; j++)
        {
            if (differenceN[j] > differenceN[j + 1])
            {
                int temp = differenceN[j];
                differenceN[j] = differenceN[j + 1];
                differenceN[j + 1] = temp;
            }
        }
    }
    cout << countN << endl;
    for (int i = 0; i < countN; i++)
    {
        cout << differenceN[i] << " ";
    }
    cout << endl;

    int countM = 0;
    int differenceM[100];
    bool usedN[100] = {false};

    for (int i = 0; i < M; i++)
    {
        bool found = false;
        for (int j = 0; j < N; j++)
        {
            if (m[i] == n[j] && !usedN[j])
            {
                found = true;
                usedN[j] = true;
                break;
            }
        }
        if (!found)
        {
            differenceM[countM] = m[i];
            countM++;
        }
    }
    for (int i = 0; i < countM - 1; i++)
    {
        for (int j = 0; j < countM - i - 1; j++)
        {
            if (differenceM[j] > differenceM[j + 1])
            {
                int temp = differenceM[j];
                differenceM[j] = differenceM[j + 1];
                differenceM[j + 1] = temp;
            }
        }
    }
    cout << countM << endl;
    for (int i = 0; i < countM; i++)
    {
        cout << differenceM[i] << " ";
    }
    cout << endl;

    int countIntersection = 0;
    int intersection[100];
    bool used[100] = {false};

    for (int i = 0; i < N; i++)
    {
        bool found = false;
        for (int j = 0; j < M; j++)
        {
            if (n[i] == m[j] && !used[j])
            {
                found = true;
                used[j] = true;
                break;
            }
        }
        if (found)
        {
            intersection[countIntersection] = n[i];
            countIntersection++;
        }
    }

    for (int i = 0; i < countIntersection - 1; i++)
    {
        for (int j = 0; j < countIntersection - i - 1; j++)
        {
            if (intersection[j] > intersection[j + 1])
            {
                int temp = intersection[j];
                intersection[j] = intersection[j + 1];
                intersection[j + 1] = temp;
            }
        }
    }
    cout << countIntersection << endl;
    for (int i = 0; i < countIntersection; i++)
    {
        cout << intersection[i] << " ";
    }
    cout << endl;

    int unionNM[200];
    int countUnion = 0;
    for (int i = 0; i < countN; i++)
    {
        unionNM[countUnion] = differenceN[i];
        countUnion++;
    }
    for (int i = 0; i < M; i++)
    {
        unionNM[countUnion] = m[i];
        countUnion++;
    }
    for (int i = 0; i < countUnion - 1; i++)
    {
        for (int j = 0; j < countUnion - i - 1; j++)
        {
            if (unionNM[j] > unionNM[j + 1])
            {
                int temp = unionNM[j];
                unionNM[j] = unionNM[j + 1];
                unionNM[j + 1] = temp;
            }
        }
    }
    cout << countUnion << endl;
    for (int i = 0; i < countUnion; i++)
    {
        cout << unionNM[i] << " ";
    }
    cout << endl;

    int countSD = 0;
    int symmetricDifference[200];

    for (int i = 0; i < countN; i++)
    {
        symmetricDifference[countSD] = differenceN[i];
        countSD++;
    }

    for (int i = 0; i < countM; i++)
    {
        symmetricDifference[countSD] = differenceM[i];
        countSD++;
    }

    for (int i = 0; i < countSD - 1; i++)
    {
        for (int j = 0; j < countSD - i - 1; j++)
        {
            if (symmetricDifference[j] > symmetricDifference[j + 1])
            {
                int temp = symmetricDifference[j];
                symmetricDifference[j] = symmetricDifference[j + 1];
                symmetricDifference[j + 1] = temp;
            }
        }
    }
    cout << countSD << endl;
    for (int i = 0; i < countSD; i++)
    {
        cout << symmetricDifference[i] << " ";
    }
    cout << endl;
    return 0;
}