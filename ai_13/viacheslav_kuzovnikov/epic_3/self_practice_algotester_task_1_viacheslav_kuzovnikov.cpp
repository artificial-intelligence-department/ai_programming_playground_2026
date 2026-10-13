/*
Євро 2012
Кузовніков В'ячеслав Євгеніойвич
ШІ-13
*/

#include <iostream>
using namespace std;
int main (){
    int lviv = 0;
    int kyiv = 0;
    int donetsk = 0;
    int kharkiv = 0;
    cin >> lviv;
    cin >> kyiv;
    cin >> donetsk;
    cin >> kharkiv;
    if (lviv < 0 || lviv > 1000){
        return 1;
    }
    if (kyiv < 0 || kyiv > 1000){
        return 1;
    }
    if (donetsk < 0 || donetsk > 1000){
        return 1;
    }
    if (kharkiv < 0 || kharkiv > 1000){
        return 1;
    }
    cout << lviv + kyiv + donetsk + kharkiv;

    return 0;
} 