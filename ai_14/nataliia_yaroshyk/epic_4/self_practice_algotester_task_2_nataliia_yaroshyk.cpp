/*  Algotester self practice
    "Лотерея"
    Ярошик Наталія
    ШІ-14 */
#include <iostream>
using namespace std;

int main(){
    int n, m;
    if (!(cin >> n >> m)) return 0;

    int** a = new int*[n];
    for(int i = 0; i < n; i++){
        a[i] = new int[m];
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }
    
    int min_of_maxes; 
 
    for(int j = 0; j < m; j++){
        int col_max = a[0][j]; 
        
        for(int i = 1; i < n; i++){
            if(a[i][j] > col_max){
                col_max = a[i][j];
            }
        }
        
        if(j == 0){
            min_of_maxes = col_max;
        } else if(col_max < min_of_maxes){
            min_of_maxes = col_max;
        }
    }
    
    cout << min_of_maxes << "\n";
    
    for(int i = 0; i < n; i++){
        delete[] a[i]; 
    }
    delete[] a; 
    return 0;
}