/*
Задача: Обробка масиву (Algotester)
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    
    int n;
    cin >> n;

    int* A = new int[n];
    
    for(int i = 0; i<n; i++)
    {
        cin >> *(A + i);
    }
    
    sort(A, A + n);

    if(*(A + n - 1) == 0)
    {
        cout << 0;
    }
    else
    {
        int count;
        if(*A != 0)
        {
            count = 1;
        }
        else count = 0;

        for(int i = 1; i < n; i++)
        {
            if(*(A + i) - *(A + i - 1) > 0) count++;
        }
        cout<<count;
    }

    delete[] A;

}
