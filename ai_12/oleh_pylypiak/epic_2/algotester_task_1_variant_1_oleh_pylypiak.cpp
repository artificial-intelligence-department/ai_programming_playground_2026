/* Задача: Algotester lab1 v1
    Автор:Пилип'як Олег
    Група: ШІ-12
*/
#include <iostream>
using namespace std;

int main(){
    double H, M;
    cin >> H >> M;
    double h1, m1, h2, m2, h3, m3;
    cin >> h1 >> m1;
    cin >> h2 >> m2;
    cin >> h3 >> m3;
    if (h1>0 && m1>0 || h2>0 && m2>0 || h3>0 && m3>0){
        cout << "NO" << endl;
    } else if (h1+h2+h3>=H || m1+m2+m3>=M){
        cout << "NO" << endl;
    }
    else {
        cout << "YES" << endl;
    }
    return 0;
}