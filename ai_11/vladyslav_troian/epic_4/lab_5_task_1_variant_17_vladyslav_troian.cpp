#include <iostream>
using namespace std;

void maxMatrix(int **mat, int rows, int cols)
{
    int a[2] = {0};
    int sum = 0;
    int max_sum = -1000000;
    int i = 0, j = 0, k = 0, q = 0;
    while (3+q <= rows) {
        k = 0;
        while (3+k <= cols) {
            i = q;
            for (; i < 3+q; i++){
                j = k;
                for (; j < 3+k; j++){
                    sum += mat[i][j];
                }
            }
            if (sum > max_sum){
                max_sum = sum;
                a[0] = q;
                a[1] = k;
            }
            k++;
            sum = 0;
        }
        q++;
    }
    cout << "Максимальна сума меншої матриці 3х3: "<< max_sum << endl;
    q = a[0];
    k = a[1];
    i = q;
    for (; i < 3+q; i++){
        j = k;
        for (; j < 3+k; j++){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int H, W;
    cin >> H >> W;
    if (H <= 2 || W <= 2){
        return -1;
    }
    int **matrix = new int*[H];
    for (int i = 0; i < H; i++){
        matrix[i] = new int[W];
    }

    cout << "Матриця" << endl;
    for (int i = 0; i < H; i++){
        for (int j = 0; j < W; j++){
            cin >> matrix[i][j];
        }
    }

    maxMatrix(matrix, H, W);

    for (int i = 0; i < H; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}