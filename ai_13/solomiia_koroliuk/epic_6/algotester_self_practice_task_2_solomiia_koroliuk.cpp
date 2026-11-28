#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

constexpr int MAX_CITIES = 500;
constexpr double PI = 3.14159265358979323846;

struct City {
    string name;
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double angle_sum = 0.0;

    static double degToRad(double deg) {
        return deg * PI / 180.0;
    }

    void setCoordsFromDeg(double lat_deg, double lon_deg) {
        double phi = degToRad(lat_deg);
        double lam = degToRad(lon_deg);
        double cos_phi = cos(phi);

        x = cos(lam) * cos_phi;
        y = sin(lam) * cos_phi;
        z = sin(phi);
    }

    double centralAngleTo(const City& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        double dz = z - other.z;
        double chord = sqrt(dx * dx + dy * dy + dz * dz);

        double half_chord = min(1.0, chord / 2.0);
        return 2.0 * asin(half_chord);
    }
};

City cities[MAX_CITIES];

int main() {

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        double lat_deg, lon_deg;
        cin >> cities[i].name >> lat_deg >> lon_deg;
        cities[i].setCoordsFromDeg(lat_deg, lon_deg);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double ang = cities[i].centralAngleTo(cities[j]);
            cities[i].angle_sum += ang;
            cities[j].angle_sum += ang;
        }
    }

    int best_idx = 0;
    for (int i = 1; i < n; ++i) {
        if (cities[i].angle_sum > cities[best_idx].angle_sum) {
            best_idx = i;
        }
    }

    cout << cities[best_idx].name << '\n';
    return 0;
}