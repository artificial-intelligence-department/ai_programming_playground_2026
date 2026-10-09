/* Євро 2012
Лисюк Андріана
ШІ-13 */
#include <iostream>

using namespace std;

int main(){
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int sum = 0;
    cin >> a >> b >> c >> d;
    if(a >= 0 && a <= 1000 && b >= 0 && b <= 1000 && c >= 0 && c <= 1000 && d >= 0 && d <= 1000 ){
     sum = a + b + c + d;   
     cout << sum;
    }
    return 0;
}

