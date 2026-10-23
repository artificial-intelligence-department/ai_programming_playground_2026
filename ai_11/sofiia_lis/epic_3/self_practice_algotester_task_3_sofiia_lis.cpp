/* 
Епік 3. self practice: Algotester, задача "Веселі каруселі"
Авторка: Софія Ліс
Група: ші-11
*/

#include <iostream>

using namespace std;

int main() {
    
    int k, n; 
    cin >> k >> n;

    int attr[100];
    for(int i = 0; i < n; i++) {
        cin >> attr[i];
    }
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(attr[i] > attr[j]) {
                int t = attr[i];
                attr[i] = attr[j];
                attr[j] = t;
            }
        }
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        if(k >= attr[i]){
            k -= attr[i];
            count += 1;
        }
    }
    cout << count << endl;
    return 0;
}
