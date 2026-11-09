#include<iostream>
using namespace std;

int main(){
    int height = 0;
    int width = 0;
    cin >> height >> width;
    char **cave = new char*[width];
    for (int c = 0; c < width; c++) {
    cave[c] = new char[height];
    }
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            cin >> cave[c][r];
        }
    }
    for(int i = 0; i < width; i++){
        int floorIndex = height-1;
            for(int j = floorIndex; j >= 0; j--){
                switch (cave[i][j])
                {
                case 'O':
                    break;

                case 'S':{
                        if(j != floorIndex){
                            cave[i][j] = 'O';
                            cave[i][floorIndex] = 'S';
                        }
                        floorIndex--;
                    break;
                }
                case 'X':{
                    floorIndex = j - 1;
                    break;
                }

                default:
                    break;
                } 
            }
        
    }

    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            cout << cave[c][r];
        }
        cout << '\n';
    }

    for (int c = 0; c < width; c++) {
        delete[] cave[c];
    }
    delete[] cave;
}