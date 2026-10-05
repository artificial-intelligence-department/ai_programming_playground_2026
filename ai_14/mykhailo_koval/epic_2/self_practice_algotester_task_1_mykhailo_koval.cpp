/* 
self_practice_algotester_task_1_mykhailo_koval
"Спекотні дня для пінгвінів"
Name: Mykhailo Koval
Group: AI-14
*/
#include <iostream>

using namespace std;

int main(){
    int l, w, u, d;
    cin >> l >> w >> u >> d;
    cout << '\n';
    
    if (l <= w && l <= u + d){
        cout << "Three times Sex on the Beach, please!" << '\n';
    } else {
        cout << "Forget about the cocktails, man!" << '\n';
    }

    return 0;
}