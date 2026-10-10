/*Epic 3 - There are two roads: One is straight, and the other...
Чернихівський Максим
Ші - 14*/

#include <iostream>
#include <cmath>

using namespace std;

int main(){
    int n;
    cin >> n;
    
    long long sum = 0;
    
    for (int i = 0; i < n; i++){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        sum += sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
    }
    
    cout << sum;
    return 0;
}