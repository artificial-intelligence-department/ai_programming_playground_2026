/*«Камінь-ножиці-папір»
Група: ШІ-11
Автор: Юлія Шведько*/

#include <iostream>
using namespace std;

int main()
{
    int r1;
    int s1;
    int p1;
    int r2;
    int s2;
    int p2;
    cin >> r1 >> s1 >> p1;
    cin >> r2 >> s2 >> p2;

    int win = 0;
    if(r1 < s2)
    win += r1;
    else
    win += s2;

    if(s1 < p2)
    win += s1;
    else
    win += p2;

    if(p1 < r2)
    win += p1;
    else
    win += r2;

    cout << win << endl;
}