//Задача №0181 "Цікава гра"
#include <iostream>
using namespace std;
int main() {
    int n,m, all;
    cin>>n>>m;
    /*Перевіряємо кількість клітинок, оскільки Бісеня ходить першим, 
    то виграє тільки тоді, коли буде непарна кількість клітинок*/
    all=m*n;
    if(all%2==0){
        cout<<"Dragon"<<endl;
    }
    else{
        cout<<"Imp"<<endl;
    }
    return 0;
}