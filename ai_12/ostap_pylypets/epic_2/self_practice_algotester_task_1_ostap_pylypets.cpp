#include <iostream>
#include <string>
using namespace std;
int main(){
    string str;
    int x, y;
    int countX = 0, countY= 0;
    cin >> str;
    cin >> x >> y;
    for (char c : str){
        if (c == 'R') countX ++;
        if( c == 'U') countY ++;
    }
    if (countX >= x && countY >= y) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}