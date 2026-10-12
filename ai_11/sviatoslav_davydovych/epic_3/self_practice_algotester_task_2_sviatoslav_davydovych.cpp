/* Задача "Кругла арена"
Умова: https://algotester.com/uk/ArchiveProblem/DisplayWithEditor/81395
Автор: Давидович Святослав
Група: ШІ-11
*/

#include <iostream>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long r, n;
    int p = 0, result = 0;

    cin >> r >> n;
    int squares[r*r];
    long long input[n], squares_id[n] = {0};

    for (int i = 0; i<n; i++){
        long long x, y;
        cin >> x >> y;

        long long sq = x*x+y*y;
        squares[sq] = 0;
        input[i] = sq;
    }

    for (int i = 0; i<n; i++){
        if (squares[input[i]]==0) {
            squares_id[p] = input[i];
            p++;
        }

        squares[input[i]]++;
    }

    for (int i = 0; i<p; i++){
        long long c = squares[squares_id[i]];
        result+=c*(c-1)/2;
    }

    cout << result;
    
    return 0;
}