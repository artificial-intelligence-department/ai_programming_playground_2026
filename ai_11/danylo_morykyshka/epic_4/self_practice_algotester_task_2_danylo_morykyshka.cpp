//Щаслива послідовність
#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int* a = new int[n];
    bool isIncreased = false;
    bool isDecreased = false;
    int count= 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    int i = 0;
    for (; i < n - 1; i++)
    {
        if(a[i] <= a[i + 1])
        {
            count++;
        }
    }
    if(count == i)
    {
        isIncreased = true;
    }
    count = 0;
    i = 0;
    for (; i < n - 1; i++)
    {
        if(a[i] >= a[i + 1])
        {
            count++;
        }
    }
     if(count == i)
    {
        isDecreased = true;
    }

    if(isIncreased || isDecreased){
        cout << "YES";
    }
    else{
        cout << "NO";
    }
    delete[] a;
    
}