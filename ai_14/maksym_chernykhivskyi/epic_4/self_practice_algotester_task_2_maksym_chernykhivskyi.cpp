/*Epic 4 - Зеник-садівник
Чернихівський Максим
Ші - 14*/

#include <iostream>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int index = (j + 2*(i % 2)) % 4;
            if (index < 2) {
                cout << "o";
            } else {
                cout << "x";
            }
        }
        cout << endl;
    }
    return 0;
}