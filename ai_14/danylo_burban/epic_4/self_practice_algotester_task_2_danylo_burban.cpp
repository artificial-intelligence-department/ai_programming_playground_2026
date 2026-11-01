/*Epic 4 - Зеник-садівник
Бурбан Данило
Ші - 14*/
#include <iostream>

using namespace std;
int main(){
    int n, m;
    cin >> n >> m;
    int **arr = new int*[n];
    for(int i = 0; i < n; i++){
        arr[i] = new int[m];
    }
    for(int i = 0; i < n; i++){
        
        for(int j = 0; j < m; j++){
            bool must_i_shift=j%2==0;
            if(i%4<2){
                arr[i][j]=1-must_i_shift;
            }else arr[i][j]=0+must_i_shift;
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(arr[i][j]){
                cout<<"x";
            }else cout<<"o";
        }
        cout<<endl;
    }


    for(int i = 0; i < n; i++){    
        delete[] arr[i];
        arr[i] = nullptr;
    }
    delete[] arr;
    return 0;
}