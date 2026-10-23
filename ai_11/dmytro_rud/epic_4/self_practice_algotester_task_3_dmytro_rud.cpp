#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip> // Необхідно для setprecision

using namespace std;

double distance(double x1, double y1, double x2, double y2) {
    return hypot(x2 - x1, y2 - y1);
}

double sphere_volume(double radius) {
    const double PI = acos(-1.0); 
    return (4.0 / 3.0) * PI * pow(radius, 3);
}

int main() {
    // Оптимізація введення-виведення для швидкості
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    
    vector<vector<int>> matrix(n, vector<int>(2, 0));

    for (int i = 0; i < n; i++) {
        cin >> matrix[i][0];
        cin >> matrix[i][1];
    }
    
    double max_dist = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            double dist = distance(matrix[i][0], matrix[i][1], matrix[j][0], matrix[j][1]);
            if (dist > max_dist) {
                max_dist = dist;
            }
        }
    }
    
    double radius = max_dist / 2.0;
    
    // Виведення з фіксованою точністю 6 знаків після коми
    cout << fixed << setprecision(6) << sphere_volume(radius) << "\n";
    
    return 0;
}
