#include <iostream>
using namespace std;

int main(){
    int n;
    int k;
    cin >> n;
    cin >> k;

    int cur = 0;   // довжина поточної серії загострених зубів
    int best = 0;  // найдовша серія

    for (int i = 0; i < n; i++){
        int a;
        cin >> a;
        if (a >= k){
            cur++;
            if (cur > best) {
                best = cur;
            }
        } else {
            cur = 0;  // кінець серії
        }
    }

    cout << best;
    return 0;
}