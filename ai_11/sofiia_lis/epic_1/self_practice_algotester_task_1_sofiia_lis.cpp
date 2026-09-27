/* 
Епік 1. self practice: Algotester, задача "A плюс B"
Авторка: Софія Ліс
Група: ші-11
*/

#include <iostream> 

using namespace std;

int main() {

    int a;
    int b;

    cin >> a;
    cin >> b;

    if (a < 0 || a > 100) {
        return 1;
    }
    if (b < 0 || b > 100) {
        return 1;
    }
    
    cout << a + b << endl;

    return 0;

}