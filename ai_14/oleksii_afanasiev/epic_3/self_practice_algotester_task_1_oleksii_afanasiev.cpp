/*
Задача: Перехід дороги (Algotester)
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>

using namespace std;

int main()
{
    int n;
    int A[100000];

    int count = 0;

    cin >> n;

    for(int i = 0; i < n; i++) cin >> A[i];
    
    for(int i = 1; i < n; i++)
    {
        if(A[i-1] % 2 != A[i] % 2) count++;
    }

    cout << count;

    return 0;
}
