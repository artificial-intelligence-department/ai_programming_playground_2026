#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
	float a_f = 1000.f;
	float b_f = 0.0001f;
	float f1 = a_f - b_f;
	float f2 = pow(f1, 3);
	float f3 = pow(a_f, 3);
	float f4 = 3 * pow(a_f, 2) * b_f;
	float f5 = f3 - f4;
	float f6 = f2 - f5;
	float f7 = pow(b_f, 3);
	float f8 = 3 * a_f * pow(b_f, 2);
	float f9 = f7 - f8;
	float f10 = f6 / f9;

	double a_d = 1000.0;
	double b_d = 0.0001;
	double d1 = a_d - b_d;
	double d2 = pow(d1, 3);
	double d3 = pow(a_d, 3);
	double d4 = 3 * pow(a_d, 2) * b_d;
	double d5 = d3 - d4;
	double d6 = d2 - d5;
	double d7 = pow(b_d, 3);
	double d8 = 3 * a_d * pow(b_d, 2);
	double d9 = d7 - d8;
	double d10 = d6 / d9;

	double all_in_one = (pow(a_d - b_d, 3) - (pow(a_d, 3) - 3 * pow(a_d, 2) * b_d)) / (pow(b_d, 3) - 3 * a_d * pow(b_d, 2));

	cout << fixed << setprecision(10);
	cout << "Float output: " << f10 << endl;
	cout << "Double output: " << d10 << endl;
	cout << "All in one output: " << all_in_one << endl;

	return 0;
}