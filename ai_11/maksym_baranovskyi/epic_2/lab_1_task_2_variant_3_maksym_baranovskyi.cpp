#include <iostream>

using namespace std;

int main(){

    cout << "Введіть число n: ";
    int n;
    cin >> n;
    
    cout << "Введіть число m: ";
    int m;
    cin >> m;

    cout << "Результат 1-го виразу (n---m):  " <<  n---m << endl;

    cout << boolalpha;
    cout << "Результат 2-го виразу (m--<n): " << (m--<n) << endl;
    cout << "Результат 3-го виразу (n++>m): " << (n++>m) << endl;


    return 0;
}