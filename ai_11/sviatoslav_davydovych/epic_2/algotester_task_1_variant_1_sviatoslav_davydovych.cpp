/* Lab 1v1 | NULP_LABS_Programming_Basics_2026
Автор: Давидович Святослав
Група: ШІ-11
 */

// для пришвидшення роботи алгоритму будемо використовувати:
// std::ios_base::sync_with_stdio(false) - вимкнення синхронізації з потоками C
// cin.tie(NULL) - вимикає зв'язування cin та cout
#include <iostream>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long H, M;
    long long Hlose, Mlose;

    cin >> H >> M;
    for (int i = 0; i < 3; i++){
        cin >> Hlose >> Mlose;
        if (Hlose && Mlose) {
            cout << "NO";
            return 0;
        };

        H-=Hlose;
        M-=Mlose;
    }
    
    if (H<=0 || M <=0){
        cout << "NO";
        return 0;
    }

    cout << "YES";

    return 0;
}
