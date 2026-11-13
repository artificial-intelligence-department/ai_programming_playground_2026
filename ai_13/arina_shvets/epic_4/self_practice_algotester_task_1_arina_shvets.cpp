#include <iostream>

using namespace std;

void countStars(char* row, int cols, int& count){
    count = 0;

    for (int j = 0; j < cols; j++){
        if (*(row + j) == '*'){
            count++;
        }
    }
}

int main(){
    int n, m, k;
    cin >> n >> m >> k;

    char** image = new char*[n];

    for (int i = 0; i < n; i++){
        image[i] = new char[m];
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> image[i][j];
        }
    }

    int trips = 0;

    for (int i = 0; i < n; i++){
        int count;

        countStars(image[i], m, count);

        trips += (count + k - 1) / k;
    }

    cout << trips << endl;

    for (int i = 0; i < n; i++){
        delete[] image[i];
        image[i] = nullptr;
    }

    delete[] image;
    image = nullptr;

    return 0;
}