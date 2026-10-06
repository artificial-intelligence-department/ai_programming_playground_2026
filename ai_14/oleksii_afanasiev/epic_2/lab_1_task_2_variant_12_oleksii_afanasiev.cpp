/*
Задача: Lab 1 task 2 (variant - 12)
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>

using namespace std;

int main()
{
    int M, N; 

    cout << "Enter n: ";
    cin >> N;
    cout << "Enter m: ";
    cin >> M;

    int m = M;
    int n = N;

    int task1 = -(-m) - ++n;
    cout << "1) - -m-++n = " << task1 << endl;
    cout << "Updated values: n = " << n << ", m = " << m << endl; 
    cout << "-----------------------------------------------" << endl;

    m = M;
    n = N;

    bool task2 = m*n < n++;
    cout << "2) m*n < n++ is " << (task2 ? "true" : "false") << endl;
    cout << "Updated values: n = " << n << ", m = " << m << endl; 
    cout << "-----------------------------------------------" << endl;

    m = M;
    n = N;

    bool task3 = n-- > m++;
    cout << "3) n-- > m++ is " << (task3 ? "true" : "false") << endl;
    cout << "Updated values: n = " << n << ", m = " << m;

    return 0;
}
