#include <iostream>
using namespace std;

void sumMatrices(int matrix_A[][3], int matrix_B[][3], int matrix_C[][3]){
     for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            matrix_C[i][j]=matrix_A[i][j]+matrix_B[i][j];
        }
    }
}

void transposeMatrix(int matrix_C[][3], int matrix_T[][3]){
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                matrix_T[i][j]=matrix_C[j][i];
            }
        }
    }
int main(){
    int matrix_A[3][3];
    int matrix_B[3][3];
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cin>>matrix_A[i][j];
        }
    }
     for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cin>>matrix_B[i][j];
        }
    }
    int matrix_C[3][3];
    int matrix_T[3][3];
    sumMatrices(matrix_A,matrix_B,matrix_C);
    transposeMatrix(matrix_C,matrix_T);
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cout<<matrix_C[i][j]<<" ";
        } cout<<endl;
    }    

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cout<<matrix_T[i][j]<<" ";
        } cout<<endl;
    }    
    return 0;
}