/* 
Епік 4. Self practice: Замовлення від стоматологів
Авторка: Софія Ліс
Група: ші-11
*/

#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    char ** rows = new char*[2];

    for(int i = 0; i < 2; i++) {
        *(rows + i) = new char[n];
        for(int j = 0; j < n; j++) {
            cin >> *(*(rows + i) + j);
        }
    }

    for(int j = 0; j < n; j++) {
        if(*(*(rows + 0) + j) == '1' && *(*(rows + 1) + j) == '1') {
        cout << "Yes";
        delete[] *(rows + 0);
        delete[] *(rows + 1);
        rows = nullptr;
        return 0;
        }   
    }
    cout << "No";
    delete[] *(rows + 0);
    delete[] *(rows + 1);
    delete[] rows;
    rows = nullptr;
    return 0;
}