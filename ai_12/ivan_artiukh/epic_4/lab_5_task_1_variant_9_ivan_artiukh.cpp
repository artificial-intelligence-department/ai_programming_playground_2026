#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void gen(int** a, const int n ){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
          a[i][j] = std::rand() % 100;  
        }
    }
}

void print_matrix(int** a, const int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

long long calc_sum( int **a, const int n){
    long long sum  = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
             sum += a[i][j];
        }
    }
    return sum;
}

int main(){
    int n  = 0;
    int size = 0;

    cout << "Введiть кiлькiсть матриць: ";
    cin >> n;
    if(cin.fail() || n <= 0){
        cout << "Помилка: некоректна кiлькiсть матриць." << endl;
        return 1;
    }

    cout << "Введiть розмір матриць: ";
    cin >> size;
    if(cin.fail() || size <= 1 || size > 20){
        cout << "Помилка: некоректний розмір матриць." << endl;
        return 1;
    }

    srand((int)(time(nullptr)));

    int **matrix = new int*[size];
    for(int i = 0; i < size; i++){
        matrix[i] = new int[size];
    }

    long long max_sum = 0;
    int greatest_matrix = 0;

    for(int i = 1; i <= n; i++){

        long long sum = 0;

        gen(matrix, size); 

        cout << "\nМатриця № " << i << endl;

        print_matrix( matrix, size);

        sum  = calc_sum(matrix, size);

        if (i == 1 || sum > max_sum) {
            max_sum = sum;
            greatest_matrix = i;
        }
    }       
    cout << "Максимальна сума: " << max_sum << "  у матриці № " << greatest_matrix << endl;
    for(int i = 0; i < size; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}
