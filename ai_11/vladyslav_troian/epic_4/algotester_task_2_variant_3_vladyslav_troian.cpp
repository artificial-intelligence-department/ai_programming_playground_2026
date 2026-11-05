#include <iostream>
using namespace std;

int main()
{
    int N;
    cin >> N;
    int *speed = new int[N];
    for (int i = 0; i < N; i++){
        cin >> speed[i];
    }

    int drone_a = 0;
    int drone_b = 0;
    while (true){
        if (N-drone_b-1 == drone_a){
            cout << drone_a+1 << " " << N-drone_b << endl;
            cout << "Collision" << endl;
            break;
        } else if (N-drone_b-2 == drone_a){
            cout << drone_a+1 << " " << N-drone_b << endl;
            cout << "Stopped" << endl;
            break;
        } else if (N-drone_b-1 < drone_a){
            cout << drone_a+1 << " " << N-drone_b << endl;
            cout << "Miss" << endl;
            break;
        }
        drone_a += speed[drone_a];
        drone_b += speed[N-drone_b-1];
    }

    delete[] speed;
    return 0;
}