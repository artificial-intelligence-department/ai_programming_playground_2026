// Практичне завдання "Редактор монохромного зображення"
// Стехнович Андрій ШІ-11
#include <iostream>
#include <iomanip>
using namespace std;
const string palette = " .:-=+*#%@";
void PrintImage(int **image, int rows, int cols) {
    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<cols; j++) {
            std::cout << image[i][j]<< " ";
        }
        std::cout << endl;
    }
}
void ShowImage(int **image, int rows, int cols) {
    std::cout<<"===================="<<endl;
    std::cout << "Зображення " << rows << " x " << cols<<":"<<endl;
    PrintImage(image, rows, cols);
    std::cout<<endl;
    std::cout<<"Малюнок:"<<endl;
    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<cols; j++) {
            std::cout << palette[image[i][j]];
        }
        std::cout << endl;
    }

}
void FindExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    int min = 10;
    int max = -1;
    float row_average[20] = {0};
    float sum=0;
    for (int i = 0; i<rows; i++) {
        float row_sum = 0;
        for (int j = 0; j<cols; j++) {
            int *row = img[i];
            sum+=*(row + j);
            row_sum+=*(row + j);
            if(*(row + j)<min) {
                min=*(row + j);
                minRow=i;
                minCol=j;
            }
            if(*(row + j)>max) {
                max=*(row + j);
                maxRow=i;
                maxCol=j;
            }
        }
        row_average[i]=row_sum/cols;
    }
    float average = sum/(rows*cols);
    std::cout<<"===================="<<endl;
    std::cout << "Найтемніший піксель: "<<min<< " (рядок " << minRow+1 << ", cтовпець "<<minCol+1<<")"<<endl;
    std::cout << "Найсвітліший піксель: "<<max<< " (рядок " << maxRow+1 << ", cтовпець "<<maxCol+1<<")"<<endl;
    std::cout << "Середня яскравість: "<<fixed<<setprecision(2)<< average<<endl;;
    std::cout<<defaultfloat;
    std::cout << "Середня по рядках: ";
    for (int i = 0; i<rows; i++) {
        std::cout<<row_average[i]<<" ";
    }
    std::cout<<endl;

}
void InvertBrightness(int **img, int rows, int cols) {
    for(int i = 0; i<rows; i++) {
        for (int j = 0; j<cols; j++) {
            int *row=img[i];
            *(row+j)=9-*(row+j);
        }
    }
    std::cout<<"===================="<<endl;
    std::cout<<"Яскравість інвертовано."<<endl;
    for(int i = 0; i<rows; i++) {
        for (int j = 0; j<cols; j++) {
            int *row=img[i];
            std::cout<<*(row+j)<< " ";
        }
        std::cout << endl;
    }
}
void swapPixels(int *a, int *b) {
    int temp=*a;
    *a=*b;
    *b=temp;
}
void Mirroring(int **image, int rows, int cols) {
    std::cout<<"===================="<<endl;
    std::cout<<"Зображення віддзеркалено."<<endl;
    std::cout<<"Початкове:"<<endl;
    for(int i =0; i<rows; i++) {
        for(int j = 0; j<cols; j++) {
            int *row=image[i];
            std::cout<<*(row+j)<<" ";

        }
        std::cout<<endl;
    }
    std::cout<<endl;
    int k = cols/2;
    for (int i=0; i<rows; i++) {
        int *row=image[i];
        for (int j=0; j<k; j++) {
            swapPixels(row+j, row+cols-j-1);
        }
    }
    std::cout<<"Результат:"<<endl;
    for(int i =0; i<rows; i++) {
        for(int j = 0; j<cols; j++) {
            int *row=image[i];
            std::cout<<*(row+j)<<" ";

        }
        std::cout<<endl;
    }
}
int** rotateRight(int **image, int rows, int cols) {
    int **rotated_image = new int*[cols];
    for (int i = 0; i<cols; i++) {
        rotated_image[i]=new int[rows];
    }
    for (int i = 0; i<cols; i++) {
        for (int j = 0; j<rows; j++) {
            rotated_image[i][j]=image[rows-1-j][i];
        }
    }
    for(int i = 0; i<rows; i++) {
        delete[] image[i];
    }
    delete[] image;
    image=nullptr;
    return rotated_image;
}
void ClearData(int **&image, int rows) {
    for(int i = 0; i<rows; i++) {
        delete[] image[i];
    }
    delete[] image;
    image=nullptr;
}
int main() {
    int rows;
    while(true) {
        std::cout << "Висота зображення: ";
        cin >> rows;
        if (cin.fail() or rows<1 or rows>20) {
            cin.clear();
            cin.ignore(10000, '\n');
            std::cout << "Ви ввели некоректні дані!"<<endl;
        } else {
            break;
        }
    }
    
    int cols;
    while(true) {
        std::cout << "Ширина зображення: ";
        cin >> cols;
        if (cin.fail() or cols<1 or cols>20) {
            cin.clear();
            cin.ignore(10000, '\n');
            std::cout << "Ви ввели некоректні дані!"<<endl;
        } else {
            break;
        }
    }
    std::cout << "Яскравість пікселів (0..9):" << endl;
    int **image = new int*[rows];
    for (int i = 0; i<rows; i++) {
        image[i]=new int[cols];
    }
    for(int i = 0; i<rows; i++) {
        for (int j = 0; j<cols; j++) {
            int a;
            while(true) {
                cin >> a;
                if(cin.fail() or a<0 or a>9) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    std::cout << "Ви ввели некоректні дані! Продовжіть воодити з того самого місця."<<endl;
                } else {
                    break;
                }
            }
            
            image[i][j]=a;
        }
    }
    int choice = -1;
    do {
        std::cout <<"==== Виберіть послугу ====\n1 - Показати зображення\n2 - Статистика яскравості\n3 - Інвертувати яскравість\n4 - Віддзеркалити по горизонталі\n5 - Повернути на 90 градусів праворуч\n0 - Вийти"<<endl;
        cin >> choice;
        if(cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        } else {
            switch(choice) {
                case 1: {
                    ShowImage(image, rows, cols);
                    break;
                }
                case 2: {
                    int minRow = 0, maxRow = 0, minCol = 0, maxCol = 0;
                    FindExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);
                    break;
                }
                case 3: {
                    InvertBrightness(image, rows, cols);
                    break;
                }
                case 4: {
                    Mirroring(image, rows, cols);
                    break;
                }
                case 5: {
                    image=rotateRight(image, rows, cols);
                    int temp = rows;
                    rows=cols;
                    cols=temp;
                    std::cout<<"===================="<<endl;
                    std::cout << "Зображення повернуто. Нові розміри: "<<rows<<" x "<<cols<< endl;
                    PrintImage(image, rows, cols);
                    break;   
                }
                default: {
                    std::cout << "Некоректний пункт меню! Спробуйте ще раз." << endl;
                    break;
                }
            }
        }

    } while (choice!=0);
    std::cout<<"===================="<<endl;
    std::cout<<"Дякуємо, що скористались редактором монохромного зображення!"<<endl;
    ClearData(image, rows);
    return 0;
}