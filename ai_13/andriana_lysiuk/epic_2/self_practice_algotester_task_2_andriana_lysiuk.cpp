/* Апельсини
Лисюк Андріана
ШІ-13 */
#include <iostream>

using namespace std;

int main(){
    int a = 0;
    int b = 0;
    int c = 0;
    cin >> a >> b >> c;
    if (a < 1 || a > 10000000000 || b < 1 || b > 10000000000 || c < 1 || c > 10000000000){
        return 1;
    }
    if (a + b > c){
        cout << "YES";
    }
    else{
        cout << "NO";
    }
    return 0;
}

