/*Epic 2 - Зуби
Франчук Андрій
Ші - 14*/

#include <iostream>
#include <string>

using namespace std;

int main(){
    int n, k, max_streak = 0;
    int streak = 0; 
    if (!(cin >> n >> k) || n < 1 || k < 1){
        cout << "Кількість зубів та межа загостреності має бути більша 0";
        return 0;
    }

    for (int i = 0; i < n; i++){
        int tooth = 0;
        cin >> tooth;
        if (tooth >= k){
            streak++;
        }else if (max_streak < streak){
            max_streak = streak;
            streak = 0;
        }
    }
    
    if (max_streak < streak){
        max_streak = streak;
    }

    cout << max_streak;
    return 0;
}