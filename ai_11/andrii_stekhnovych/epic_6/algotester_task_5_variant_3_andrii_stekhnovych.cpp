#include <iostream>
#include <cmath>
using namespace std;
int main(){
    int N, M;
    cin >> N >> M;
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    int** matrix = new int*[N];
    for (int i=0; i<N; i++) {
        matrix[i]=new int[M];
        for (int j=0; j<M; j++) {
            matrix[i][j]=0;
        }
    }
    int max=0;
    for(int i=0; i<N; i++) { //rows
        for(int j=0; j<M; j++) { //cols
            int delta_x=abs(x-i);
            int delta_y=abs(y-j);
            int res=delta_x+delta_y;
            matrix[i][j]=res;
            if(res>max) {
                max=res;
            }
        }
    }
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            matrix[i][j]=max-matrix[i][j];
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    for (int i=0; i<N; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix=nullptr;
    


}