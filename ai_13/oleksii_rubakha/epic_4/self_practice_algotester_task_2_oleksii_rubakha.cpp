
/* 
    Симетрична матриця
    Олексій Рубаха
    ШІ-13
*/

#include <iostream>

int main(){

    int n;
    std::cin >> n;

    char arr[1000][1000];

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            std::cin >> arr[i][j];
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (arr[i][j] != arr[j][i]){
                std::cout << "No";
                return 0;
            }
        }
    }

    std::cout << "Yes";

    return 0;
}