/*Task 2 algotester variant 1
Ім'я: Сукач Андрій
Група: ШІ-14*/
#include <iostream>

using namespace std;
    int main() {
        int n;
        cin >> n;
        int r[100000]= {0};
        for (int i = 0; i < n; i++) {
            cin >> r[i];
        }
        if (n == 1){
            cout << 0;
            return 0;
        }
int minFatigue = 1000000000;
int maxFatigue = -1000000000;

        for (int i = 0; i < n; i++) {
            if (minFatigue > r[i]){
                minFatigue = r[i];
            }
            if (maxFatigue < r[i]){
                maxFatigue = r[i];
            }
        }
      int newMin = 1000000000;
      int newMax = -1000000000;
        int case1, case2;
        for (int i = 0; i < n; i++){
            if (r[i] == minFatigue){
                
                for (int j = 0; j < n; j++){
                    if (j != i && newMin > r[j]){
                        newMin = r[j];
                    }
                }
                break;
            }
        }
        case1 = maxFatigue - newMin;
        for (int i = 0; i < n; i++){
            if (r[i] == maxFatigue){
                for (int j = 0; j < n; j++){
                    if (j != i && newMax < r[j]){
                        newMax = r[j];
                    }
                }
                break;
            }
        }
        case2 = newMax - minFatigue;
            if (case1 < case2){
                cout << case1;
            }
            else{
                cout << case2;
            }

        return 0;
    }