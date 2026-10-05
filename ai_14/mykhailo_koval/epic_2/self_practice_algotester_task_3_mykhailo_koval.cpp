/* 
self_practice_algotester_task_3_mykhailo_koval
"Цікава гра"
Name: Mykhailo Koval
Group: AI-14
*/
#include <iostream>

using namespace std;

int main(){
    int n;
    int m;
    cin >> n >> m;
    cout << '\n';

    if (n < 1 || n > 100 || m < 1 || m > 100){
        return 1;
    }
    int s = n * m;

    if (s % 2 == 0){
        cout << "Dragon";
    } else if (s % 2 == 1){
        cout << "Imp";
    }
    return 0;
}