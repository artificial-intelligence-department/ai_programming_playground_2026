/*Epic 3 - Літня школа
Бурбан Данило
Ші - 14*/
#include <iostream>
using namespace std;
int main(){
    int n=0;
    int k=0;

    
    int team_of_1=0;
    int team_of_2=0;
    int team_of_3=0;
    cin>>n>>k;

    int remaining = n;
   
    
    
    remaining = n - k;

    team_of_3 = remaining / 2;
    team_of_2 = remaining % 2;
    team_of_1 = k - team_of_2 - team_of_3;

    if (n < k || n > 3 * k) {
        cout << "Impossible";
        return 0;
    }

    for (int i = 0; i < team_of_1; ++i) cout << 1 << " ";
    for (int i = 0; i < team_of_2; ++i) cout << 2 << " ";
    for (int i = 0; i < team_of_3; ++i) cout << 3 << " ";
    cout << endl;

    
    return 0;
}