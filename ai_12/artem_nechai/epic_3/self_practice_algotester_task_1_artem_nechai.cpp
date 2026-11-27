#include <iostream>

using namespace std;

int main() {
	int n, m, s;
	int arr[1000];
	cin >> n;
	cin >> m;
	cin >> s;

	int m_pos = n / 2;

	if (n == 1) {
		if (m != s) {
			cout << "-1";
			return 0;
		}
		arr[0] = m;
	} 
	else if (n == 2) {
		if (m > s ||  m * 2 < s) {
			cout << "-1";
			return 0;
		}
		arr[0] = s-m;
		arr[1] = m;
	} 
	else {
		
		int s1 = (n - m_pos) * m;

		if (s1 > s) {
			cout << "-1";
			return 0;
		}

		for (int i = 0; i < m_pos; i++) {
			arr[i] = 0;
		}

		for (int i = m_pos; i < n; i++) {
			arr[i] = m;
		}

		arr[n-1] += s - s1;
	}

	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}

	return 0;
}
