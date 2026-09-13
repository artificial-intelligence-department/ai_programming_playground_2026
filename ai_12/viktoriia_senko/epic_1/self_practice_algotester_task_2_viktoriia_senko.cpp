//Задача №2101 "Крісла"
#include <iostream>
using namespace std;
int main() {
    int a, b, c;
    cin>>a>>b>>c;
    //перевіряємо, чи кількість зареєстрованих і незареєстрованих менша за кількість крісел
    if (a+c<=b){
        cout<<"All"<<endl;
    }
    //якщо перша умова не проходить, дивимося, чи вистачає місць зареєстрованим
    else if(a<=b){
        cout<<"All registered"<<endl;
    }
    else {
        cout<<"Bad organizers"<<endl;
    }
    return 0;
}