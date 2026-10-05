/*
Task: self_practice_algotester_task_3 (Спекотнi днi пiнгвiнiв)
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/
#include <iostream>

using namespace std;
int main (){
    
    long long l = 0, w = 0, u = 0, d = 0;
    cin >> l >> w >> u >> d;  // 𝑙, 𝑤, 𝑢 та 𝑑 — діаметр коктейлю, ширина роту і на скільки дюймів щелепи можуть розкритися відповідно

    if(l < 1 || w < 1 || u < 1 || d < 1){
        return 0;
    }

    if(l <= w && l <= (u + d)){
        cout << "Three times Sex on the Beach, please!" << endl;
    }else {
        cout << "Forget about the cocktails, man!" << endl;
    }




    return 0;
}
