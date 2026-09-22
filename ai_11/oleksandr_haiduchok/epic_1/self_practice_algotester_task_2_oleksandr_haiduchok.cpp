/* Спекотнi днi пiнгвiнiв
Гайдучок Олександр
ШІ-11*/
#include <iostream>
#include <string>
using namespace std;
int main ()
{
    int l, w, u, d;
    cin >> l;
    cin >> w;
    cin >> u;
    cin >> d;
    if  (l <= w && u + d >= l){
        cout << "Three times Sex on the Beach, please!";
    }
        else {
            cout << "Forget about the cocktails, man!";
        }
    return 0;
}
