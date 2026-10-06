# include <iostream> 
# include <cmath>
using namespace std;

int main(){
    long long H, M, h, m;
    bool alive;
    alive = true;
    cin >> H >> M;
    if (H >= 1 && H <= pow(10 , 12) && M >= 1 && M <= pow(10 , 12)) {} else {alive = false;}
    cin >> h >> m;
    if (h > 0 && m > 0 || !(h >= 0 && h <= pow(10 , 12)) || !(m >= 0 && m <= pow(10 , 12))) {alive = false;} else {H = H - h; M = M - m;}
    
    cin >> h >> m;
    if (h > 0 && m > 0 || !(h >= 0 && h <= pow(10 , 12)) || !(m >= 0 && m <= pow(10 , 12))) {alive = false;} else {H = H - h; M = M - m;}
    
    cin >> h >> m;
    if (h > 0 && m > 0 || !(h >= 0 && h <= pow(10 , 12)) || !(m >= 0 && m <= pow(10 , 12))) {alive = false;} else {H = H - h; M = M - m;}
    
    if (H <= 0 || M <= 0 || alive == false) {cout << "NO"; return 0;} else {cout << "YES"; return 0;}
  
}
