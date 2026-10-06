/* Стипендія №1792
Artem Mnikh 
AI_14
*/
#include <iostream>

using namespace std;

int main(){
    int n, score;
    cin >> n;
    int pidv = 1;
    int nostyp = 0;
    for (int i = 0; i < n; ++i){
        cin >> score;
        if (score < 51) {nostyp = 1; break;}
        else if (score < 90) pidv = 0;
    }
    if (nostyp) cout << "Zabud pro stypendiiu";
    else if (pidv) cout << "Pidvyshchena";
    else cout << "Zvychaina";
    return 0;
}
