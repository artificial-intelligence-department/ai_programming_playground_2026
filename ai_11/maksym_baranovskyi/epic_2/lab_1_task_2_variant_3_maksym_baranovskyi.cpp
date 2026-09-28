#include <iostream>

using namespace std;

int main(){

    cout << "Введіть число n: ";
    int n;
    cin >> n;
    
    cout << "Введіть число m: ";
    int m;
    cin >> m;

    int result1 = n---m;
    cout << "Результат 1-го виразу (n---m):  " << result1 << endl;

    bool result2 = m--<n;
    cout << boolalpha;
    cout << "Результат 2-го виразу (m--<n): " << result2 << endl;

    bool result3 = n++>m;
    cout << "Результат 3-го виразу (n++>m): " << result3 << endl;


    return 0;
}