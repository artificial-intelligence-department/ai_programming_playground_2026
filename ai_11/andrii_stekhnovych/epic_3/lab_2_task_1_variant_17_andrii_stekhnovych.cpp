#include <iostream>
#include <iomanip>
using namespace std;
int main(){
        const double eps = 0.0001;
        double sum = 0;
        double a_current = 0.1;
        int n = 1;
        sum+=a_current;
        while (a_current>=eps) {
            a_current = a_current*n/10;
            sum+=a_current;
            n++;
            
        } 
        cout << "Сума ряду:" << fixed << setprecision(4) << sum << endl;
        

}
