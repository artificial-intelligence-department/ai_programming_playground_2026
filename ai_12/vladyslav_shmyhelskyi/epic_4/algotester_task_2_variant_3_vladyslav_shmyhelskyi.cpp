#include <iostream>

using namespace std;
int main()
{
    int N;
    cin >> N;
    int arr[N];
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }

    int positiond1 = 1;
    int positiond2 = N;

    int copyN[N];
    for (int i = 0; i < N; i++)
    {
        copyN[i] = arr[N - 1 - i];
    }
    for (int i = 0; i < N; i++)
    {

        if (positiond1 == positiond2)
        {
            cout << positiond1 << " " << positiond2 << endl;
            cout << "Collision";
            return 0;
        }
        else if (positiond1 > positiond2 - 1)
        {
            cout << positiond1 << " " << positiond2 << endl;
            cout << "Miss";
            return 0;
        }
        else if (positiond1 + 1 == positiond2)
        {
            cout << positiond1 << " " << positiond2 << endl;
            cout << "Stopped";
            return 0;
        }
        int step1 = arr[positiond1 - 1];
        int step2 = arr[positiond2 - 1];
        positiond1 = positiond1 + step1;
        positiond2 = positiond2 - step2;
    }
}