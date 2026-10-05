#include <iostream>

int main()
{
	int n = 5;
	int m = 5;

	std::cout << "Введіть n: ";
	std::cin >> n;
	std::cout << "Введіть m: ";
	std::cin >> m;

	int temp_n = n;
	int temp_m = m;

	int res1 = n---m;	//n-- - m;
	std::cout << temp_n << "---" << temp_m << " = "<< res1 << std::endl;

	n = temp_n;
	m = temp_m;

	bool res2 = m--<n;	//m-- < n;
	std::cout << temp_n << "--< " << temp_m << " is " << res2 << std::endl;

}
