#include <iostream>
#include <iomanip>

void output(int **image, int rows, int cols){

    for(int i =0; i <rows; i++){
        for(int j =0; j <cols; j++){
            std::cout << *(*(image + i)+j) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

}

void enter_rc(int &rows, int &cols, bool &fail){  //уводимо висоту та ширину зображення

    std::cout << "Висота зображення: ";
    std::cin >> rows;
    if(std::cin.fail() || rows < 1 || rows > 20){
        std::cout << "Не припустиме значення. Вихід з програми.";
        fail = true;
        return;  
    }

    std::cout << "Ширина зображення: ";
    std::cin >> cols;
    if(std::cin.fail() || cols < 1 || cols > 20){
        std::cout << "Не припустиме значення. Вихід з програми.";
        fail = true;
        return; 
    }

}

void enter_image(int rows, int cols, int **image, bool &fail){ //вводимо яскравість

    std::cout << "Яскравість пікселів (0..9): " << std::endl;
    for(int i =0; i <rows; i++){
        for(int j =0; j <cols; j++){
            std::cin >> image[i][j];
            if(std::cin.fail() || image[i][j] < 0 || image[i][j] > 9){
                std::cout << "Не припустиме значення. Вихід з програми.";
                fail = true;
                return;  
            }
        }
    }

}

void image_output(int rows, int cols, int **image){ //виводимо зображення

    //виводимо зображення у звичайному вигляді 

    std::cout << "\nЗображення " << rows << " x " << cols << ":" << std::endl;
    output(image, rows, cols);

    //виводимо сам малюнок

    char palette[9] = {'.', ':', '-', '=', '+', '*', '#', '%', '@'};

    std::cout << "\nМалюнок:" << std::endl;
    for(int i =0; i <rows; i++){
        for(int j =0; j <cols; j++){
            if(*(*(image + i)+j) == 0) std::cout << "  ";
            else std::cout << palette[(*(*(image + i)+j)-1)] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){ //статистика 

    minRow = 0; minCol = 0; maxRow = 0; maxCol = 0;
    int max = image[0][0]; int min = image[0][0];
    for(int i =0; i < rows; i++){  //шукаємо максимальну(мінімальну) яскравість, шукаємо рядки, стовпці з цими значеннями  
        int* row = image[i];
        for(int j =0; j < cols; j++){
            if(*(row + j) > max){ 
                max = *(row + j);
                maxRow = i;
                maxCol = j;
            }
            if(*(row + j) < min){ 
                min = *(row + j);
                minRow = i;
                minCol = j;
            }
        }
    }

    std::cout << "Найтемніший піксель: " << min << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << std::endl;
    std::cout << "Найсвітліший піксель: " << max << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << std::endl;

    float sum_image = 0;
    float arithmetic_mean = 0;
    for(int i =0; i < rows; i++){  //шукаємо суму всіх пікселів 
        int* row = image[i];
        for(int j =0; j < cols; j++){
            sum_image += *(row + j);
        }
    }
    arithmetic_mean = sum_image / (rows * cols);  //середня яскравість всього зображення
    sum_image = 0;

    std::cout << "Середня яскравість: " << std::fixed << std::setprecision(2) << arithmetic_mean << std::endl << "Середня по рядках: ";
    float arithmetic_mean_rows = 0;
    for(int i =0; i < rows; i++){  //шукаємо суму пікселів за рядками 
        int* row = image[i];
        for(int j =0; j < cols; j++){
            sum_image += *(row + j);
        }
        arithmetic_mean_rows = sum_image / cols; //середня яскравість за рядком
        std::cout << std::fixed << std::setprecision(1) << arithmetic_mean_rows << " "; 
        sum_image = 0;
        arithmetic_mean_rows = 0;
    }
    std::cout << std::endl;

}

void invert_image(int rows, int cols, int **image){

    for(int i =0; i <rows; i++){
        for(int j =0; j <cols; j++){
            *(*(image + i) + j) = 9 - *(*(image + i) + j);
        }
    }

    std::cout << "\nЯскравість інвертовано." << std::endl;
    output(image, rows, cols);

}

void swapPixels(int *a, int *b){
    int t_t = 0;
    t_t = *a; *a = *b; *b = t_t;
}

void reflection(int **image, int rows, int cols){

    std::cout << "Зображення віддзеркалено." << std::endl << "Початкове:" << std::endl;
    output(image, rows, cols);

    int n_reflection = cols / 2;
    for(int i =0; i < rows; i++){
        for(int j =0; j < n_reflection; j++){
            swapPixels(&image[i][j], &image[i][cols - 1 - j]);
        }
    }

    std::cout << "Результат:" << std::endl;
    output(image, rows, cols);

}

int** rotateRight(int** img, int rows, int cols){

    int** image_right = new int*[cols];
    for(int i =0; i <cols; i++){
        image_right[i] = new int[rows];
    }

    for(int i =0; i <cols; i++){
        for(int j =0; j <rows; j++){
            *(*(image_right + i) + j) = *(*(img + (rows - 1 - j)) + i);
        }
    }

    for(int i =0; i < rows; i++){
    delete[] img[i]; 
    }  
    delete[] img;
    img = nullptr;

    return image_right;

}

void Rotate_Output(int **&image, int &rows, int &cols){

    image = rotateRight(image, rows, cols);
    int time_t = 0;
    time_t = rows; rows = cols; cols = time_t;
    std::cout << "\nЗображення повернуто. Нові розміри: " << rows << " x " << cols << std::endl;
    output(image, rows, cols);

}

int main(){

    int rows = 0, cols = 0;   //висота та ширина зображення
    int minRow = 0, minCol = 0, maxRow = 0, maxCol = 0;
    bool fail = false; 
    enter_rc(rows, cols, fail); if(fail) return 0;


    int **image = new int*[rows];  //масив(матриця) зображення(яскравості)
    for(int i = 0; i < rows; i++){
        image[i] = new int[cols];      
    }
    enter_image(rows, cols, image, fail); 
    if(fail){
        for(int i =0; i < rows; i++){
            delete[] image[i]; 
        }  
        delete[] image;
        image = nullptr;
        return 0;
    }
 
    int choice;

    do{

        menu:

        std::cout << std::left << std::setw(18) << "\nПункт" << "Операція" << std::endl;
        std::cout << std::left << std::setw(12) << "1" << "Показати зображення" << std::endl;
        std::cout << std::left << std::setw(12) << "2" << "Статистика яскравості" << std::endl;
        std::cout << std::left << std::setw(12) << "3" << "Інвертувати яскравість" << std::endl;
        std::cout << std::left << std::setw(12) << "4" << "Віддзеркалити по горизонталі" << std::endl;
        std::cout << std::left << std::setw(12) << "5" << "Повернути на 90 градусів праворуч" << std::endl;
        std::cout << std::left << std::setw(12) << "0" << "Вийти" << std::endl;

        std::cout << "\n>";
        std::cin >> choice;
        if(std::cin.fail() || choice < 0 || choice > 5){
            std::cout << "Ви ввели недопустиме значення, спробуйте ще раз." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            goto menu;
        }
        std::cin.ignore(10000, '\n');

        switch(choice){

            case 1:
            image_output(rows, cols, image);
            break;

            case 2:
            findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);
            break;

            case 3:
            invert_image(rows, cols, image);
            break;

            case 4:
            reflection(image, rows, cols);
            break;

            case 5:
            Rotate_Output(image, rows, cols);
            break;

            default: 
            std::cout << "Вихід з програми.";
            for (int i =0; i < rows; i++){
                delete[] image[i]; 
            }  
            delete[] image;
            image = nullptr;
            return 0;

        }


    }while(choice != 0);

    for (int i =0; i < rows; i++){
        delete[] image[i]; 
    }  
    delete[] image;
    image = nullptr;


    return 0;
}