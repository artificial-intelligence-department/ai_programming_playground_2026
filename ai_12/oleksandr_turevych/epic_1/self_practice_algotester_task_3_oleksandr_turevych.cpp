#include <iostream>

int main() {
	int a, b;
	std::cin >> a >> b;
	if((a * b)%2 == 0)
	{
		std::cout << "Dragon";
	}
	else
	{
		std::cout << "Imp";
	}
	return 0;
}
