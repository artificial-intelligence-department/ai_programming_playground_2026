#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	int n;
	cin >> n; //кількість компаній
	if (n <= 0)
	{
		return 1;
	}

	vector <int> l(n);
	vector <string> name(n);
	for (int i = 0; i < n;i++)
	{
		cin >> l[i];
		name[i] = to_string(i + 1);
	}

	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++) {
			int temp_l = l[i];
			string temp_name = name[i];
			int j;
			for (j = i; j >= gap && l[j - gap] > temp_l; j -= gap) {
				l[j] = l[j - gap];
				name[j] = name[j - gap];
			}

			l[j] = temp_l;
			name[j] = temp_name;
		}
	}
	for (int i = 0;i < n;i++)
	{
		cout << name[i] << " ";
	}


}