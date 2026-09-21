#include <iostream>

int main() {
	int a, b, c, d;
	std::cin >> a >> b >> c >> d;
	if(a > b || a > c+d)
	{
		std::cout << "Forget about the cocktails, man!";
	}
	else
	{
		std::cout << "Three times Sex on the Beach, please!";
	}
	return 0;
}
