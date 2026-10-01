/*Epic 2 - Коля, Вася і теніс
Франчук Андрій
Ші - 14*/

#include <iostream>
#include <string>

using namespace std;

int main(){
    int n = 0;
    if(!(cin >> n) || n <= 0){
        cout << "Кількість подач має бути більша 0";
        return 0;
    }

    int kscore = 0;
    int vscore = 0;
    int kfscore = 0;
    int vfscore = 0;

    string s;
    cin >> s;

    for (int i =0; i < n; i++){
        if (s[i] == 'K'){
            kscore++;
        }else if (s[i] == 'V'){
            vscore++;
        }else{
            cout << "Кількість символів не співпадає з кількістю матчів";
            return 0;
        }
        if ((kscore >= 11 || vscore >= 11) && (abs(kscore - vscore) >= 2)){
            if (kscore > vscore){
                kfscore++;
                kscore = 0;
                vscore = 0;
            }else{
                vfscore++;
                kscore = 0;
                vscore = 0;
            }
        }
    }
    cout << kfscore << ":" << vfscore << endl;
    if (kscore > 0 || vscore > 0){
        cout << kscore << ":" << vscore << endl;
    }
    return 0; 

}