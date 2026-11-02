/*
Задача: Lab 2v1 (Algotester)
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int A[100000];
    int N;
    cin>>N;
    
    for(int i = 0; i < N; i++)
    {
        cin>>A[i];
    }
    
    sort(A, A+N);
    
    if(N == 1)
    {
        cout << 0;
        return 0;
    }
    else if(N == 2)
    {
        cout << A[0];
    }
    else
    {
       if(A[N-2] - A[0] < A[N-1] - A[1]) cout << A[N-2] - A[0];
       else cout << A[N-1] - A[1];
    }
    
    return 0;
}

