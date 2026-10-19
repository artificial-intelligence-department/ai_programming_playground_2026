/*
Задача: Найбільша пара (Algotester)
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>

using namespace std;

int main()
{
    int n;
    int A[1000];

    cin >> n;
    for(int i = 0; i < n; i++) cin >> A[i];

    for(int i = 0; i < n - 1; i++)
    {  
        for(int j = 0; j < n - i - 1; j++)
        {   
            if(A[j] > A[j+1])
            {
                int t = A[j];
                A[j] = A[j+1];
                A[j+1] = t;
            }            
        }
    }  

    int sum = 0;

    for(int i = 0; i < n/2; i++)
    {   
        int sum_i = A[i] + A[n - 1 - i];
        if(sum_i > sum) sum = sum_i;
    }

    cout << sum;

    return 0;
}
