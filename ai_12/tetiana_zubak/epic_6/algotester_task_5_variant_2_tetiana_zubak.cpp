/* 
Алготестер, варіант 2
Зубак Тетяна
ШІ-12
*/
#include <cstdio>

using namespace std; 

int main(){
    int n, m; 
    scanf("%d %d", &n, &m); 
    char grid[n][m+1]; 
    for(int i = 0; i < n; i++){
        scanf("%s", grid[i]);
    }
    for(int i = 0; i < m; i++){
        int bottom = n - 1;
        for(int j = n - 1; j >= 0; j--){
            if(grid[j][i] == 'X'){
                bottom = j - 1;
            }
            else if(grid[j][i] == 'S'){
                grid[j][i] = 'O';
                grid[bottom][i] = 'S';
                bottom--;
            }
        }
    }
    for(int i = 0; i < n; i++){
        printf("%s\n", grid[i]);
    }

    return 0;
}