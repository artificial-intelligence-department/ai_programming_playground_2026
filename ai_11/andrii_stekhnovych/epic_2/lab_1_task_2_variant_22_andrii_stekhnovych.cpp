#include <iostream>
using namespace std;
int main(){
    // Ввід n, m
    int n;
    cout<<"Enter n:";
    cin >> n;
    int m;
    cout<<"Enter m:";
    cin >> m;
    // Виведення розрахунків
    cout << "++n*++m=" <<++n*++m<<endl;
    cout << fixed << boolalpha;
    cout << "m++<n: " <<(m++<n)<<endl;
    cout << "n++>m: " <<(n++>m)<<endl;


}