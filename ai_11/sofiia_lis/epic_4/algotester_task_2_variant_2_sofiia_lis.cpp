/* 
Епік 4. algotester_task_2_variant_2
Авторка: Софія Ліс
Група: ші-11
*/

#include <iostream>

using namespace std;

const int N = 100000;

int main() {

    int n;
    int a, b, c;
    int m;
    cin >> n;
    int array[N];

    for(int i = 0; i < n; i++) {
        cin >> array[i];
    }

    cin >> a >> b >> c;

    for(int i = 0; i < n; i++) {
        if(array[i] == a || array[i] == b || array[i] == c) {
            for(int j = i; j < n-1; j++) {
                array[j] = array[j + 1];   
            }
            n--;
            i--;
        } 
    }
    
    if(n <= 1) {
        cout << "0";
        return 0;
    }

    else {
        m = n-1;
    }
    
    int brray[N];
    for(int i = 0; i < m; i++) {
        brray[i] = (array[i] + array[i + 1]);
    }

    cout << m << endl;

    for(int i = 0; i < m; i++) {
        cout << brray[i] << " ";
    }

    return 0;
}