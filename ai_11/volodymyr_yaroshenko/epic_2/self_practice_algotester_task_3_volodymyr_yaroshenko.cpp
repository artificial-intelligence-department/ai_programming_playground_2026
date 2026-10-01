#include <iostream>

using namespace std;

int main() {
int r_m, p_m, s_m, r_z, p_z, s_z, res = 0;
cin >> r_m >> s_m >> p_m;
cin >> r_z >> s_z >> p_z;
if((r_m < 0 && r_m > 1000 &&
    s_m < 0 && s_m > 1000 &&
    p_m < 0 && p_m > 1000 &&
    r_z < 0 && r_z > 1000 &&
    s_z < 0 && s_z > 1000 &&
    p_z < 0 && p_z > 1000)) {
    cout << "End" << endl;
    return -1 ;
} 
if ( (r_m + s_m  + p_m + r_z + s_z + p_z) < 1 || (r_m || s_m  || p_m || r_z || s_z || p_z) > 1000) {
    return -1;
}
if(r_m / s_z == 1) {
    res ++;
}
if(s_m / p_z == 1) {
    res++;
}
if(p_m / r_z == 1) {
    res++;
}
cout << res << endl;

    return 0;
}