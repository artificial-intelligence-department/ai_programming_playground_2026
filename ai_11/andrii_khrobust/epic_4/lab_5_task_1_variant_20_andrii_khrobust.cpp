#include <iostream>
using namespace std;

int main(){
    int n,m;
    int a[100][100];
    cin >> n >> m;
    cout << "enter elements of your matrix: ";
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> a[i][j];
        }
    }
    int min = 0;
    bool found = false;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int count = 0;
            for(int k=0;k<n;k++){
                for(int l=0;l<m;l++){
                    if(a[i][j] == a[k][l]){
                        count++;
                    }
                }
            }
            if(count == 1){
                if(found == false || min > a[i][j]){
                    min = a[i][j];
                    found = true;
                }
            }
        }
    }
    cout<<min;
    return 0;
}