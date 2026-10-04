/*Algotester Task 1 Variant 2
Автор:Сенько Вікторія
Група: ШІ-12 group3*/
#include <iostream>
#include <algorithm>//бібліотека для знаходження мінімального та максимального значення
using namespace std;
int main( ) {
    long long h1, h2, h3, h4, d1, d2, d3, d4;
    cin>>h1>>h2>>h3>>h4; 
    cin>>d1>>d2>>d3>>d4;
    bool tripping=false;
    //Перевіряємо чи ніжка не є коротшою за відпиляний шматок
    if (h1<d1 || h2<d2 || h3<d3 || h4<d4){
        cout<<"ERROR"<<endl;
        return 0;
    }
    //Довжина 1 ніжки після відпилювання
    h1-=d1;
    //Перевіряємо чи після кожного відпилювання найдовша поки ніжка не перевищує вдвічі найкоротшу
    if (max(max(h1, h2), max(h3, h4)) >= 2 * min(min(h1, h2), min(h3, h4))) tripping=true;
    h2-=d2;
    if (max(max(h1, h2), max(h3, h4)) >= 2 * min(min(h1, h2), min(h3, h4))) tripping=true;
    h3-=d3;
    if (max(max(h1, h2), max(h3, h4)) >= 2 * min(min(h1, h2), min(h3, h4))) tripping=true;
    h4-=d4;
    if (max(max(h1, h2), max(h3, h4)) >= 2 * min(min(h1, h2), min(h3, h4))) tripping=true;

    //Перевіряємо чи стоїть стіл
    if(!tripping && h1==h2 && h2==h3 && h3==h4) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
    return 0;
}