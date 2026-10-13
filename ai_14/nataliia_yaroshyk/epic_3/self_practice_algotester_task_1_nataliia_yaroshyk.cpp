/* Algotester self practice 1
    "Марічка і печиво"
    Наталія Ярошик 
    ШІ-14
*/
#include <iostream>
using namespace std;

int main(){
    int n;
    long long a;
    long long count = 0;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> a;
        count += (a - 1);
    }
    cout << count;
}