//Замовлення від квітникарів
//https://algotester.com/uk/ArchiveProblem/DisplayWithEditor/71056

#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    int array[n][m];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> array[i][j];
        }
    }

    int maxSum = 0;

    for(int i = 0; i < n; i++){
        int rowSum = 0;

        for(int j = 0; j < m; j++){
            rowSum += array[i][j];
        }

        int maxColSum = 0;

        for(int j = 0; j < m; j++){
            int colSum = 0;

            for(int k = 0; k < n; k++){
                if(k != i){
                    colSum += array[k][j];
                }
            }

            if(colSum > maxColSum){
                maxColSum = colSum;
            }
        }

        if(rowSum + maxColSum > maxSum){
            maxSum = rowSum + maxColSum;
        }
    }

    cout << maxSum;

    return 0;
}