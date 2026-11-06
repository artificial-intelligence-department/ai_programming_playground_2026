// "Лотерея"
#include <iostream>
using namespace std;

const int MAX_N = 1000;
const int MAX_M = 1000;

int a[MAX_N][MAX_M];

int main() {
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }
    int resultMinMax = 100000;
    for(int j = 0; j < m; j++){
        int columnMax = a[0][j];
    
    for(int i = 1; i < n; i++){
        if(a[i][j] > columnMax){
            columnMax = a[i][j];
        }
    }
    if(columnMax < resultMinMax){
        resultMinMax = columnMax;
      }
    }
    cout << resultMinMax;
    return 0;
}
