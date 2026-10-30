#include <iostream>
#include <string>

int main(){
    int N; 
    std::cin >> N;
    std::string *a = new std::string[N];
    std::cin.ignore();

    for(int i = 0; i < N; i++){
        std::getline(std::cin, *(a + i));
    }

    int number = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < (*(a + i)).length(); j++){
            if(a[i][j] == '#' && (j == 0 || a[i][j - 1] != '#')){
                number++;
            }
        }
    }

    std::cout << number;

    delete[] a;
    a = nullptr;
    return 0;
}