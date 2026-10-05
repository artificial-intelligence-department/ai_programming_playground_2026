#include <iostream>

int main()
{
    long a, b, c;
    std::cin >> a >> b >> c;

	if (a+b > c)
	{
		std::cout << "YES";
		return 0;
	}
	else { std::cout << "NO"; return 0; }
}

