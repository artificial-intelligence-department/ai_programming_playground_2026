//Запити на матриці
#include <iostream>
using namespace std;

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
int main(){
    ios_base::sync_with_stdio(false); //вимикає синхрон. з потоками с і с++
    cin.tie(NULL); //дозволяє cin зчитувати дані без постійного примусового очищення буфера cout

    int rows;
    cin >> rows;
    if(cin.fail() || rows <= 0) return 0;

    int cols;
    cin >> cols;
    if(cin.fail() || cols <= 0) return 0;
    //виділяєм память під кожен ел
    int** matrix = new int*[rows];
    for( int i = 0; i < rows; i++){
        matrix[i] = new int[cols];      
    }
    //елементи матриці
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cin >> matrix[i][j];
        }
    }

    int q;
    cin >> q;

    while(q--){
        int type;
        cin >> type;

        if(type == 1){
            int x1, y1, x2, y2, h, w;
            cin >> x1 >> y1 >> x2 >> y2 >> h >> w;
            
            //перетвооримо на індекси
            x1--; y1--;
            x2--; y2--; 

            for(int i = 0; i < h; i++){
                for( int j = 0; j < w; j++){
                    swap(&matrix[x1 + i][y1 + j], &matrix[x2 + i][y2 + j]);
                }
            }

        } else if(type == 2){
            int x, y;
            cin >> x >> y;

            // перехід до індексів
            x--; y--;

            //значення елемента за координатами
            cout << matrix[x][y] << "\n";
        }
    }

    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}