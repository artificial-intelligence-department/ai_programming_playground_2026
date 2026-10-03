/* 
Завдання "Цікава гра" списку задач Algotester 
Белаш Матвій Валерійович
ШІ-12
*/
#include <iostream>
using namespace std;

int main(){

    short n, m;
    cin >> n >> m;
    short S = n * m;

    if(S % 3 == 0){
        cout << "Dragon";
        return 0;
    }else if((S % 3 == 1) || (S % 3 == 2)){
        if (S % 2 == 0){
            cout << "Dragon";
            return 0;
        } else if(S % 2 == 1){
            cout << "Imp";
        }
    }
    return 0;
}