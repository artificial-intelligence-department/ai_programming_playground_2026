#include <iostream>
#include <iomanip>

int main()
{
	float a = 1000;
	float b = 0.0001;

	float f_monom1 = (a - b) * (a - b) * (a - b);
	float f_monom2 = (a * a * a - 3 * a * b * b);

	float f_numerator = f_monom1 - f_monom2;

	float f_monom3 = b * b * b;
	float f_monom4 = 3 * a * a * b;

	float f_denominator = f_monom3 - f_monom4;

	float f_res = f_numerator / f_denominator;

	std::cout << std::setprecision(15) << f_res << std::endl;

	double a2 = 1000;
	double b2 = 0.0001;

	double d_monom1 = (a2 - b2) * (a2 - b2) * (a2 - b2);
	double d_monom2 = (a2 * a2 * a2 - 3 * a2 * b2 * b2);

	double d_numerator = d_monom1 - d_monom2;

	double d_monom3 = b2 * b2 * b2;
	double d_monom4 = 3 * a2 * a2 * b2;

	double d_denominator = d_monom3 - d_monom4;

	double d_res = d_numerator / d_denominator;

	std::cout << std::setprecision(15) << d_res << std::endl;
}