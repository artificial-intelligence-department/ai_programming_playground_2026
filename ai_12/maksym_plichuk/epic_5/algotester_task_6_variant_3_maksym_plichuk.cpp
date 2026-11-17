#include <iostream>
#include <string>
using namespace std;

int main()
{

    int N;
    cin >> N;
    int **arr = new int *[N];
    for (int i = 0; i < N; i++)
    {
        arr[i] = new int[N];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            char ch;
            cin >> ch;
            arr[i][j] = ch - '0';
        }
    }

    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        int x, y;
        cin >> x >> y;

        int xIndex = x - 1;
        int yIndex = y - 1;
  
        if (arr[xIndex][yIndex] != 0)
        {
            cout << 1 <<"\n";
            cout << arr[xIndex][yIndex]<<"\n\n";
            continue;
        }
        else
        {
            int *avaliable = new int[N];
            int count = 0;

            for (int num = 1; num <= N; num++)
            {
                bool isUsed = false;

                for (int i = 0; i < N; i++) {
                    if (arr[i][yIndex] == num) {
                        isUsed = true;
                        break;
                    }
                }
                if (!isUsed) {
                    for (int j = 0; j < N; j++) {
                        if (arr[xIndex][j] == num)
                        {
                            isUsed = true;
                            break;
                        }
                    }
                }
                
                if (!isUsed){
                    avaliable[count] = num;
                    count++;
                }
            }
            if (count == 0){
                cout << 0 << "\n";
            }
            else {
                cout << count << "\n";
                for (int i = 0; i < count; i++) {
                   cout << avaliable[i] << " ";
                }
                cout << "\n\n";
            }
            delete[] avaliable;
        }
    }

    for (int i = 0; i < N; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
    return 0;
}