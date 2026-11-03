/*Алготестер задача 2 варіант 3
Максімко Павло - СШІ-13*/

#include <iostream>

using namespace std;

int main()
{
    const int N_MAX = 1000;
    int N;
    cin >> N;
    if(cin.fail() || N < 1 || N > N_MAX)
    {
        cout << "Неправильно! N повинне бути від 1 до " << N_MAX << "!" << endl;
        return 0;
    }

    int x = 1, y = N; 
    int a[N_MAX];

    for(int i = 0; i < N; i++)
    {
        cin >> a[i];
        if(cin.fail() || a[i] < 1 || a[i] > 5)
        {
            cout << "Неправильно! Крок повинен бути від 1 до 5!" << endl;
            return 0;
        }
    }

    int i = 0;
    int j = N - 1;
    while(true)
    {
        if(x == y) 
        {
            cout << x << " " << y << endl;
            cout << "Collision" << endl;
            break;
        }
        if(x > y) 
        {
            cout << x << " " << y << endl;
            cout << "Miss" << endl;
            break;
        }
        if(x + 1 == y)
        {
            cout << x << " " << y << endl;
            cout << "Stopped" << endl;
            break;
        }
        x += a[i];
        y -= a[j];
        i += a[i];
        j -= a[j];
    }

    return 0;
}