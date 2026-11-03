/*Задача: Дракон і Кросворд
Виконав: Сукач Андрій (ШІ-14)*/
#include <iostream>
#include <string>
using namespace std;

int main(){
    char crossword[1005][1005];
    bool deleted[1005][1005];
    int n,m;
    cin >> n >> m;
for (int i = 0; i < n; i++){ //ввід
    for (int j = 0; j < m; j++){
        cin >> crossword[i][j];
    }
}

for (int i = 0; i < n; i++){ // всі елементи перебір
    for (int j = 0; j < m; j++){
        bool has_duplicate = false;
   
    for (int k = 0; k < m; k++){ // для стовпців
    if (k != j && crossword[i][j] == crossword[i][k]) {
                    has_duplicate = true;
                    break;
                }
            }
     if (!has_duplicate) { // для рядків
                for (int k = 0; k < n; k++) {
                    if (k != i && crossword[i][j] == crossword[k][j]) {
                        has_duplicate = true;
                        break;
                    }
                }
        
            }
            if (has_duplicate) {// викреслення
                deleted[i][j] = true;
    }
}
}
for (int i = 0; i < n; i++){ // вивід без викреслених
    for (int j = 0; j < m; j++){
        if (!deleted[i][j]) cout << crossword[i][j];
    }
}
return 0;
}