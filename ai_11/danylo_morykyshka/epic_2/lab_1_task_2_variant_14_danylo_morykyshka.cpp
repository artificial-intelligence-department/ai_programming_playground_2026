#include <iostream>

using namespace std;

int main()
{
    cout << "Enter m: " ;
    int m;
    cin >> m;
    cout << "Enter n: ";
    int n;
    cin>> n;
    cout << "float results: "<< endl;
    cout << "1) m+--n: " << m+--n << endl;
    cout << "2) m++<++n: " << (m++<++n) << endl;
    cout << "3) n--<--m: " <<( n--<--m) << endl;
}