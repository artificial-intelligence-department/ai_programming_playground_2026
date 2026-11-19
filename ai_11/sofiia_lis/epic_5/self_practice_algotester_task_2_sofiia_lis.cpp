/* 
Епік 5. self_practice_algotester_task_2 "Буквозабирання"
Авторка: Софія Ліс
Група: ші-11
*/

#include <iostream>
#include <string>
using namespace std;

bool good(string ts, string tt, int l) { // чи залишиться кінцевий рядок, якщо спочатку забрали l символів
    if(l < 0 || l > ts.size() - tt.size()) {
        return false;
    }

    for(int i = 0; i < tt.size(); i++) { // цикл для порівняння кінцевого і частини початкового, що залишилась після l відрізань зліва
        if(ts[l+i] != tt[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int test;
    cin >> test;

    for(int i = 0; i < test; i++) {
        string s, t;
        cin >> s >> t;

        int k = s.size() - t.size();
        
        bool fin;
        if(k % 2 == 1) {
            fin = good(s, t, (k/2)) && good(s, t, (k/2+1));
        }
        else {
            fin = good(s, t, (k/2)) || (good(s, t, k/2-1) && good(s, t, k/2+1));
        }      
    cout << (fin ? "Sergei" : "Larry") << endl;
    }
    
    return 0;
}