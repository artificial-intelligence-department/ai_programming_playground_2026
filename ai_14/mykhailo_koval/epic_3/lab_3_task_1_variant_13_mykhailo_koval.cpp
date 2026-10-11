#include <iostream>
#include <cmath>

int main(){
    const double a = 0.2, b = 1.0;
    const int k = 10;// кількість кроків
    const int n = 10;// для випадку а
    const double eps = 0.0001; // для випадку б
    double h = (b - a) / k;
    std::cout << "\t\tОбчислення функції" << std::endl;

    for(int i = 0; i <= k; i++){
        double x = a + i * h;
        double d = (x - 1.0) / (x + 1.0);
        double d2 = d * d;

        double s1 = 0;
        double q = d;
        for(int m = 0; m <= n; m++){
            s1 += q / (2.0 * m + 1.0);
            q *= d2;
        }

        q = d;
        double s2 = 0, current;
        int g = 0;
        do{
            current = q / (2.0 * g + 1.0);
            s2 += current;
            q *= d2;
            g++;
        } while(std::fabs(current) >= eps);

        std::cout << "X = " << x << " SN = " << s1 << " SE = " << s2 << " Y = " << 0.5 * std::log(x) << std::endl;

    }
}