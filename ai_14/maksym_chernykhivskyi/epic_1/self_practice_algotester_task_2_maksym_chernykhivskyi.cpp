#include <iostream>
using namespace std;

int main() {
    int N, M, cells;
    cin >> N >> M;
    
    if (N >= 1 && N <= 100 && M >= 1 && M <= 100) {
        cells = N * M;
        if (cells%2 == 0){cout << "Dragon";} else {cout << "Imp";};

     } else {return 1;}
    
    
    return 0;
}

