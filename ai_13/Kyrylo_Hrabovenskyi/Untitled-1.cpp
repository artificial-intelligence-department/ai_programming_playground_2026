#include <iostream>
#include <clocale> 
#include <windows.h>

using namespace std;

int main()
{

	cout << "How much Hp does your hero have\n";

	long Hp;

	cin >> Hp;

	cout << "How much mana does hero have\n";

	long mana;

	cin >> mana;

	long Hi = 1000;

	long Mi = 1000;

	for (int i = 0; i < 3; i++)
	{

		Hp = Hp - 1000;

		mana = mana - 1500;

	}

	if (mana < 0)
	{

		cout << "you loose";
		return  0;

	}

	if (Hp < 0)
	{

		cout << "you loose";
		return 0;

	}
}