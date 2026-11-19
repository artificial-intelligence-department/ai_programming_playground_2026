/* 
Епік 5. lab_6_variant_3
Авторка: Софія Ліс
Група: ші-11
*/


#include <iostream>
#include <string>

using namespace std;

void check(string * sudo, int n, int ** coord, int q) {
    for(int i = 0; i < q; i++) {
        int coordrow = coord[i][0] - 1;
        int coordcol = coord[i][1] - 1;
        if(sudo[coordrow][coordcol] - '0' != 0) {
            cout << 1 << endl << sudo[coordrow][coordcol] << endl << endl;
            continue;
        }
        int counter = 0;
        int * arr = new int[n];

        for(int j = 1; j <= n ; j++) {
            bool flag = true;
            for(int k = 0; k < n; k++) {
                if(sudo[coordrow][k] - '0' == j) {
                    flag = false;
                    break;
                }
            }
            for(int k = 0; k < n; k++) {
                if(sudo[k][coordcol] - '0' == j) {
                    flag = false;
                    break;
                }
            }
            if(flag) {
            arr[counter] = j;
            counter++;
            }
        }
        cout << counter << endl;
        for(int i = 0; i < counter; i++) {
            cout << arr[i] << ' ';
        }
        cout << endl << endl;

        delete[] arr;
    }

}

int main() {

    int n;
    cin >> n;

    cin.ignore();

    string * sudo = new string [n];

    for(int i = 0; i < n; i++) {
        getline(cin, sudo[i]);
    }

    int q;
    cin >> q;
    
    int ** coord = new int * [q];

    for(int i = 0; i < q; i++) {
        coord[i] = new int[2];
    }
    
    for(int i = 0; i < q; i++) {
        for(int j = 0; j < 2; j++) {
            cin >> coord[i][j];
        }
    }

    check(sudo, n, coord, q);
    
    for(int i = 0; i < q; i++) {
        delete[] coord[i];
    }
    delete[] coord;
    delete[] sudo;

    return 0;
}