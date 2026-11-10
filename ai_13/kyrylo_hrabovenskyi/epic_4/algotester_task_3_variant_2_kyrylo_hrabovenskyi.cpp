#include <iostream>
using namespace std;


int main()
{
    // Обмеження за умовою N, M <= 100, тому розміру 105 цілком достатньо
    const int limit = 105;

    int N;
    if (!(cin >> N)) return 0;
    int A[limit];
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }


    int M;
    if (!(cin >> M)) return 0;
    int B[limit];
    for (int i = 0; i < M; i++)
    {
        cin >> B[i];
    }
    int k = 0;
    // Шукаємо кількість спільних елементів
    for (int i = 0; i < M; i++)
    {
        for (int q = 0; q < N; q++)
        {
            if (B[i] == A[q])
            {
                k++;
            }
        }
    }

    // Вивід результату у два окремі рядки, як вимагає умова
    cout << k << "\n";
    cout << N + M - k << "\n";


    return 0;
}


