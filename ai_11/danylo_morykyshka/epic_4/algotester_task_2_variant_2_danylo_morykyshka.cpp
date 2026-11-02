#include <iostream>
using namespace std;
const int MAX_LENGTH = 100000;
int main()
{
    int n;
    cin >> n;
    int arr[MAX_LENGTH];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int a;
    int b;
    int c;
    cin >> a >> b >> c;
    int newLen = 0;
    int tempArr[MAX_LENGTH];
    for (int i = 0; i < n; i++)
    {
        if(arr[i] != a && arr[i] != b && arr[i] != c){
            tempArr[newLen] = arr[i];
            newLen++;
        }

    }
    if(newLen > 0)
    {

        cout << newLen - 1<< endl;
    }
    else{
        cout << 0;
    }
    for (int  i = 0; i < newLen - 1; i++)
    {
        cout << tempArr[i] + tempArr[i + 1] << " ";
    }
    
}