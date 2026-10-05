/*
Algotester lab 1v1
Artem Mnikh
AI_14
*/
#include <iostream>

using namespace std;

int main(){
    long long hp, mana;
    long long spell_hp, spell_mana;
    cin >> hp >> mana;
    for (int i = 0; i < 3; i++){
        cin >> spell_hp >> spell_mana;
        if (spell_hp && spell_mana){
            cout << "NO";
            return 0;
        }
        if ((hp -= spell_hp) <= 0 || (mana -= spell_mana) <= 0){
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
    return 0;
}
