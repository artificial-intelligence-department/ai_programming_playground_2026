/* 
Епік 4. algotester_task_3_variant_2
Авторка: Софія Ліс
Група: ші-11
*/

#include <iostream>

using namespace std;

const int A = 100;

int main() {
    int N, M;
    cin >> N;
    
    int array[A];
    
    for(int i = 0; i < N; i++) {
        cin >> array[i];
    }
    cin >> M;
    
    int brray[A];

    for(int i = 0; i < M; i++) {
        cin >> brray[i];
    }

    int areInBoth = 0;
    int uniqueCharacters = 0;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(array[i] == brray[j]) {
                areInBoth++;
            }
        }
    }

    uniqueCharacters = (N+M) - areInBoth;
    
    cout << areInBoth << endl;
    cout << uniqueCharacters << endl;

    return 0;
}