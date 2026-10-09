/*
Назва: self practice | Народна вакцина
Автор: Бичковський Володимир
Група: ШІ-11
*/

#include <iostream>
using namespace std;
int main(){
    long long a, b;
    long long arifmetic_sum;
    cin >> a >> b;
    if((a-b)%12==0){
    }
    else{
        cout << "-1" << endl;
        return 0;
    }
    arifmetic_sum = ((a+b)/2)*13;
    cout << arifmetic_sum << endl;
}