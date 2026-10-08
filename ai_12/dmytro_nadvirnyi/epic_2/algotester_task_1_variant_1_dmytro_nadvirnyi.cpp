#include <iostream>
using namespace std;



    int main() {
    long long Hp;
    long long Mana;
    long long h, m;
   
    cin >> Hp;
    cin >> Mana;
    for (int i=0; i<3; i++){
        cin >> h;
        cin >> m;

        if (h>0 && m>0){
        cout<< "NO" << endl;
        return 0;
        }
        Hp=Hp-h;
        Mana=Mana-m;

    }
    if (Hp>0 && Mana>0){
        cout<< "YES" << endl;
    }
    else{
        cout<< "NO" << endl;
    }


    return 0;
    }