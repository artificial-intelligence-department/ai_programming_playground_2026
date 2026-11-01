#include <iostream>
#include <iomanip>
//1 пункт меню
void showImage(int **image, int rows, int cols){
    std::cout << "Зображення " << rows << " x " << cols << ":\n";
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            std::cout << image[i][j] << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    std::cout << "Малюнок:\n";
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(image[i][j] == 0){
                std::cout << " ";
            } else if (image[i][j] == 1){
                std::cout<< ".";
            } else if (image[i][j] == 2){
                std::cout<< ":";
            } else if (image[i][j] == 3){
                std::cout<< "-";
            } else if (image[i][j] == 4){
                std::cout<< "=";
            } else if (image[i][j] == 5){
                std::cout<< "+";
            } else if (image[i][j] == 6){
                std::cout<< "*";
            } else if (image[i][j] == 7){
                std::cout<< "#";
            } else if (image[i][j] == 8){
                std::cout<< "%";
            } else if (image[i][j] == 9){
                std::cout<< "@";
            }
        }
        std::cout << '\n';
    }
}

//2 пункт меню
void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
    minRow = 0; 
    minCol = 0;
    maxRow = 0;  
    maxCol = 0;
    int min = image[0][0];
    int max = image[0][0];
    for (int i = 0; i < rows; i++){
        int *row = image[i];
        for (int j = 0; j < cols; j++) {
            int element = *(row + j);
            if(element < min){
                min = *(row + j); 
                minRow = i; 
                minCol = j;
            }
            if (element > max){
                max = *(row + j); 
                maxRow = i; 
                maxCol = j;
            }
        }
    }
}

void avgBrightness(int **image, int rows, int cols){
    int sum = 0;
    int totalElements = rows * cols;
    for(int i = 0; i < rows; i++){
        int *row = image[i];
        for(int j = 0; j < cols; j++){
            sum += *(row + j);
        }
    }
    double avgBright = (double)sum / (double)totalElements;
    std::cout << "Середня яскравість: ";
    std::cout << std::fixed << std::setprecision(2) << avgBright << std::endl;

    std::cout << "Середня по рядках: ";
    for(int i = 0; i < rows; i++){
        int *row = image[i];
        double sumRow = 0;
        for(int j = 0; j < cols; j++){
            sumRow += *(row + j);
        }
        double avgRow = sumRow / cols;
        std::cout << std::fixed << std::setprecision(2) << avgRow << " ";
    }
    std::cout << '\n';
}

void brightnessStats(int **image, int rows, int cols){
    int minRow, minCol, maxRow, maxCol;
    findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);
    std::cout << "Найтемніший піксель: " << *(*(image + minRow) + minCol) << " " << "(рядок " << minRow + 1 << ", " << "стовпець " << minCol + 1<< ")\n"; 
    std::cout << "Найсвітліший піксель: " << *(*(image + maxRow) + maxCol) << " " << "(рядок " << maxRow + 1 << ", " << "стовпець " << maxCol + 1 << ")\n";

    avgBrightness(image, rows, cols);
}

//3 пункт меню
void invertBrightness(int **image, int rows, int cols){
    std::cout << "Яскравість інвертовано.\n";
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            image[i][j] = 9 - image[i][j];
            std::cout << image[i][j] << " ";
        }
        std::cout << '\n';
    }
}

//4 пункт меню
void swapPixels(int *a, int *b){
    int temp = (*a);
    (*a) = (*b);
    (*b) = temp;
}

void mirror(int **image, int rows, int cols){
    std::cout << "Зображення віддзеркалено.\n";
    std::cout << "Початкове: \n";
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            std::cout << image[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << '\n';
    std::cout << "Результат: \n";
    if(cols == 1){
        std::cout << "Зображення занадто мале для відзеркалення\n";
        return;
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols / 2; j++){
            swapPixels(&image[i][j], &image[i][cols - 1 - j]);
        }
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            std::cout << image[i][j] << " ";
        }
        std::cout << "\n";
    }
}

//5 пункт меню
int** rotateRight(int** image, int rows, int cols){
    int **rotated = new int*[cols];
    for(int i = 0; i < cols; i++){
        rotated[i] = new int[rows];
    }
    
    for(int i = 0; i < cols; i++){
        for(int j = 0; j < rows; j++){
            rotated[i][j] = image[rows - 1 - j][i];
        }
    }

    for(int i = 0; i < rows; i++){
        delete[] image[i];
        image[i] = nullptr;
    }
    delete[] image;

    return rotated;
}

void rotated(int** &image, int &rows, int &cols){
    image = rotateRight(image, rows, cols);

    int temp = rows;
    rows = cols;
    cols = temp;

    std::cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << '\n';
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            std::cout << image[i][j] << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

int main(){
    int rows, cols;
    int option;

    bool notValR = false;
    bool notValC = false;
    do{
        std::cout << "Висота пікселів зображення: ";
        std::cin >> rows;
        notValR = std::cin.fail();
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        std::cout << "Ширина пікселів зображення: ";
        std::cin >> cols;
        notValC = std::cin.fail();
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    } while (notValC || notValR || rows < 1 || rows > 20 || cols < 1 || cols > 20);

    int **image = new int*[rows];
    for(int i = 0; i < rows; i++){
        image[i] = new int[cols];
    }
    
    std::cout << "Яскравість пікселів(0-9): \n";
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            bool valid;
            do{
                valid = true;
                std::cin >> image[i][j];
                if(std::cin.fail() || image[i][j] < 0 || image[i][j] > 9){
                    std::cout << "Введіть валідні значення: \n";
                    valid = false;
                    i = 0;
                    j = 0;
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                }
            } while(!valid);
        }
    }
    std::cout << '\n';

    do{
        std::cout << "Пункт\t" << "Операція\n";
        std::cout << "1\t" << "Показати зображення\n";
        std::cout << "2\t" << "Статистика яскравості\n";
        std::cout << "3\t" << "Інвертувати яскравість\n";
        std::cout << "4\t" << "Віддзеркалити по горизонталі\n";
        std::cout << "5\t" << "Повернути на 90 градусів праворуч\n";
        std::cout << "0\t" << "Вийти\n";
        
        bool notVal = false;
        do{
            std::cout << "Виберіть пункт меню: ";
            std::cin >> option;
            notVal = std::cin.fail();
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        } while (notVal || option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 0);
        
        switch (option){
            case 1:
            showImage(image, rows, cols);
            break;
            case 2:
            brightnessStats(image, rows, cols);
            break;
            case 3:
            invertBrightness(image, rows, cols);
            break;
            case 4:
            mirror(image, rows, cols);
            break;
            case 5:
            rotated(image, rows, cols);
            break;
            case 0:
            break;
            default:
            break;
        }
    } while (option != 0);


    for(int i = 0; i < rows; i++){
        delete[] image[i];
        image[i] = nullptr;
    }
    delete[] image;
    image = nullptr;
}