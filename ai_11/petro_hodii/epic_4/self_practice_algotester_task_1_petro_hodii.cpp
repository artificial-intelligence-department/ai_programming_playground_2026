#include <iostream>
#include <string>

using namespace std;

int main(){
    int num; 
    cin >> num;
    bool res = true;

    int** matrix = new int*[num];
    for(int i = 0; i < num; i++){
        matrix[i] = new int[num];
    }

    for(int i = 0; i < num; i++){
        string temp;
        cin >> temp;
        for(int j = 0; j < num; j++){
            matrix[i][j] = temp[j] - '0';
        }
    }

    for(int i = 0; i < num; i++){
        for(int j = i+1; j < num; j++){
            if(matrix[i][j] != matrix[j][i]){
                res = false;
                break;
            }
        }
        if(!res){break;}
    }

    if(res){cout << "Yes";}
    else{cout << "No";}

    for(int i = 0; i < num; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
    return 0;
}