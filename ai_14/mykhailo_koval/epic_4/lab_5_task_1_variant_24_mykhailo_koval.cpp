#include <iostream>

int main(){
    int r, c;
    std::cin >> r >> c;
    if(r != c){
        std::cout << "Матриця повинна бути квадратною";
        return 1;
    }
    int **matrix = new int*[r]; 
    for(int i = 0; i < r; i++){
        matrix[i] = new int[c];
    }

    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            std::cin >> matrix[i][j];
        }
    }

    int *mainD = new int[r];
    int index = 0;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            if(i == j){
                mainD[index] = matrix[i][j];
                index++;
            }
        }
    }

    bool bigger = false;
    int count = 0;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            bigger = false;
            for(int x = 0; x < r; x++){
                if(matrix[i][j] <= mainD[x]){
                    bigger = true;
                    break;
                }
            }
            if(!bigger){
                count++;
            }
        }
    }

    std::cout << count;

    for(int i = 0; i < r; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] mainD;
    matrix = nullptr;
    mainD = nullptr;
    return 0;
}