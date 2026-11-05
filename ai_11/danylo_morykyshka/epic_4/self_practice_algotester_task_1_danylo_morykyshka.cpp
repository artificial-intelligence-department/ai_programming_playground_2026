//Цікавий масив
#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    int generalSum = 0;
    for (int i = 0; i < n; i++)
    {
        generalSum += a[i];
    }
    int smallSum = 0;
    bool isFound = false;
    for (int i = 0; i < n; i++)
    {
        smallSum += a[i];
        if(smallSum == generalSum - smallSum)
        {
            isFound = true;
            break;
        }
    }

    if(isFound)
    {
        cout << "TAK";
    }
    else
    {
        cout << "NI";
    }
    
    delete[] a;
    
}