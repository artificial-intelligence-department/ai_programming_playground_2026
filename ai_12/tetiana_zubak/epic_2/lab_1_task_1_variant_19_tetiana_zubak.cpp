/* 
Практика Алготестер, варіант 3
Зубак Тетяна
ШІ-12
*/
#include <iostream>
#include <string>

using namespace std;

int main() {
    int N;
    cin >> N;
    int square[N];
    for(int i = 0; i < N; i++) {
        cin >> square[i];
    }
    int squarel = 0, square2 = N - 1;
    int dleft, dright;
    string result;
    while(true){
    if(squarel == square2){
        result = "Collision";
        break;
    }
    else if(squarel > square2){
        result = "Miss";
        break;
    }
    else if(squarel + 1 == square2){
        result = "Stopped";
        break;
    }

    dleft = square[squarel];
    squarel += dleft;
    dright = square[square2];
    square2 -= dright;
    }

    cout << squarel + 1 << " " << square2 + 1 << endl << result << endl;                      

    return 0;
}