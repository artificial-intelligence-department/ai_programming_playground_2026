/*
селф практіс завдання 3, Найкращий акамулятор
*/
#include <iostream>
#include <string>
using namespace std;
int main(){
    int n;
    char fav;
    cin >> n >> fav;
    string best = "A";
    string *s = new string[n];
    for(int i = 0; i<n; i++){
        cin >> s[i];
        int pos = 0;//пробігаємося по індексах поки не знайдемо симвло більший за fav по аскіі
        while(pos < s[i].length() && s[i][pos] <= fav)pos++;//треба <= а не < бо після символів що збігаються з fav можуть ще бути менші ніж fav
        s[i].insert(pos, 1, fav);
        if(best == "A")best = s[0];//поскільки "A" зустріти не можна безпечно приписую найкращому значення першого а потім порівнюю з іншими
        if(s[i] < best)best = s[i];//для стрінгів доста використати < замість strcmp від якого б ми чекали від'ємне число 
    }
    cout << best;
    delete[] s;
    return 0;
}