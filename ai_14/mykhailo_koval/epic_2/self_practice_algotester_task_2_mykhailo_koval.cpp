/* 
self_practice_algotester_task_2_mykhailo_koval
"Скільки заплатили?"
Name: Mykhailo Koval
Group: AI-14
*/
#include <iostream>

using namespace std;

int main(){
    int a, b;
    cin >> a >> b;
    cout << '\n';
    int max;
    int min;

    if (a > b){
        max = a;
        min = b;
    } else {
        max = b;
        min = a;
    }

    if (max - min < 2){
        cout << "-1";
    } else {
        int c = max - 1;
        cout << c;
    }

    return 0;
}