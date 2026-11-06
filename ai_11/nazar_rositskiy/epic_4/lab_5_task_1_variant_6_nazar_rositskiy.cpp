#include <iostream>
//#include <cstdlib>

using namespace std;

void getPoints(int** matrix, int rows, int cols){

    //Пошук точок
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            bool isMaxRow = true;
            for(int k = 0; k < cols; k++){
                if (matrix[i][k] > matrix[i][j]){
                    isMaxRow = false;
                    break;
                }
            }

            bool isMinRow = true;
            for(int k = 0; k < cols; k++){
                if (matrix[i][k] < matrix[i][j]){
                    isMinRow = false;
                    break;
                }
            }

            bool isMaxCol = true;
            for(int k = 0; k < rows; k++){
                if (matrix[k][j] > matrix[i][j]){
                    isMaxCol = false;
                    break;
                }
            }

            bool isMinCol = true;
            for(int k = 0; k < rows; k++){
                if (matrix[k][j] < matrix[i][j]){
                    isMinCol = false;
                    break;
                }
            }
            
            if((isMaxCol && isMinRow) || (isMinCol && isMaxRow)){
                cout << i+1 << " " << j+1 << endl;
            }

        }
    }
}

int main(){
    //Ініціалізація змінних
    int rows, cols;

    //питаємо розміри матриці
    std::cout << "Введіть кількість рядків: ";
    std::cin >> rows;
    if(cin.fail() || rows <= 0){
        cout << "Неприпустимі розміри";
        return 0;
    }

    std::cout << "Введіть кількість стовпців: ";
    std::cin >> cols;
    if(cin.fail() || cols <= 0){
        cout << "Неприпустимі розміри";
        return 0;
    }

    //виділяємо пам'ять під матрицю
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    //введення матриці
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> matrix[i][j];
        }
    }

    //Виклик функції що шукає та виводить сідлові точки
    getPoints(matrix, rows, cols);

    //Видалення матриці з пам'яті
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

}