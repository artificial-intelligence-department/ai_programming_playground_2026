// Задача 1893 - Portraits
//https://algotester.com/en/ArchiveProblem/DisplayWithEditor/70926

#include <iostream>
using namespace std;

int main(){
    int n, m, k;
    cin >> n >> m >> k;
    int current = 0;
    int trips = 0;
    float res = 0.0;
    char** arr = new char*[n];
    for (int i = 0; i < n; i++){
        arr[i] = new char[m];
        for (int j = 0; j < m; j++){
            cin >> arr[i][j];
        }
    }

    for (int i = 0; i < n; i++){
        current = 0;
        for (int j = 0; j < m; j++){
            if (arr[i][j] == '*') current++;
            if (current == k){
                trips++;
                current = 0;
            }
    }
    if (current > 0) trips++;
    }
    cout << trips;
}