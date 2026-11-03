/*Epic 4 - Зеник-садівник
Чернихівський Максим
Ші - 14*/

#include <iostream>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    int **arr = new int*[n];
    for (int i = 0; i < n; i++){
        arr[i] = new int[m];
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int index = (j + 2*(i % 2)) % 4;
            if (index < 2) {
                arr[i][j] = 0;
            } else {
                arr[i][j] = 1;
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if (arr[i][j] == 0) {
                cout << "o";
            } else {
                cout << "x";
            }
        }
        cout << endl;
    }
    return 0;
}