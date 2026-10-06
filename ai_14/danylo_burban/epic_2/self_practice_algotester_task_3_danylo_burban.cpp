/*Epic 2 -
Зуби
Ші - 14*/
#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int n, k, maxStreak = 0;
    int streak = 0;

    cin >> n;
    cin >> k;

    for (int i = 0; i < n; i++) {
        int tooth;
        cin >> tooth;

        if (tooth >= k) {
            streak++;
            maxStreak = max(maxStreak, streak);
        } else {
            streak = 0;
        }
    }

    cout << maxStreak << endl;
    return 0;

}