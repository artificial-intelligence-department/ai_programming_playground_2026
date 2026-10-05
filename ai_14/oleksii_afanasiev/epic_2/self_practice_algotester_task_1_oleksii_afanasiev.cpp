/*
Задача: Підтягування (Algotester)
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>

using namespace std;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    
    int r = n * k;
    
    cout << (r > m ? r : m);

    return 0;
}
