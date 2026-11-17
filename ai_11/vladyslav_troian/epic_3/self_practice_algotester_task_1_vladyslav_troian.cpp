#include <iostream>
using namespace std;

int main()
{
    int n = 0;
    int m = 0;
    int num = 0;
    cin >> n >> m;

    //Відповіддю буде сума доданки, якої будуть найбільші значення отримані студентами
    int trees[m] = {0};
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> num;
            if (num > trees[j]){
                trees[j] = num;
            }
        }
    }
    int min_sum = 0;
    for (int i = 0; i < m; i++){
        min_sum += trees[i];
    }
    cout << min_sum << endl;
    return 0;
}

// https://algotester.com/uk/ArchiveProblem/DisplayWithEditor/20091#mySolutions