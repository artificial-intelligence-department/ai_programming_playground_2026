#include <iostream>
using namespace std;
int main()
{
    long long N;
    cin >> N;
    long long a[N] = {0};
    long long left = 0;
    long long right = N-1;
    for (long long i = 0; i < N; i++) {
        cin >> a[i];
    }

    while(true){
        if(left == right){
            cout << left+1 <<" " << right+1 <<endl;
            cout << "Collision";
            break;
        }
        else if(left > right){
            cout << left+1<< " " << right+1 << endl;
            cout << "Miss";
            break;
        }
        else if(left + 1 == right){
            cout << left+1 << " " << right+1<<endl;
            cout << "Stopped";
            break;
        }
        left += a[left];
        right -= a[right];
    }
    

    return 0;
}