/* Жеребець і кобила №2151
Artem Mnikh 
AI_14
*/

#include <iostream>

using namespace std;

int main(){
    long x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cout << (x1 * x2 > 0 && y1 * y2 > 0 ? "Yes": "No");
    return 0;
}
