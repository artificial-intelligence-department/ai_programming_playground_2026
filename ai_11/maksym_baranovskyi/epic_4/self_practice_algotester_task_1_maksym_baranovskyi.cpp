//Портрети
//https://algotester.com/uk/ArchiveProblem/DisplayWithEditor/70926

#include <iostream>
using namespace std;

int main(){

    int n, m, k;
    cin >> n >> m >> k;

    char arr[n][m];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> arr[i][j];
        }
    }

    int current = 0;
    int counter = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(arr[i][j] == '*'){
                current++;
            }
            if(current == k){
                counter++;
                current = 0;
            }
        }
        if(current > 0){
            counter++;
        }
        current = 0;
    }

    cout << counter;
    return 0;
}