#include <iostream>
using namespace std;

int main(){
long long H, M;
cin >> H >> M;
bool possible = true;

long long total_h = 0;
long long total_m = 0;

for (int i = 0; i < 3; ++i){
long long h_i, m_i;
cin >> h_i >> m_i;
if (h_i > 0 && m_i > 0) {
    possible = false;
}
total_h += h_i;
total_m += m_i;
}

if (possible && (H - total_h >0 ) && (M - total_m > 0)){
    cout<< "YES" << endl;
} else {
    cout<< "NO" << endl;
}
return 0;

}

