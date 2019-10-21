//Kamil Cinner IIST 3.2
#include <iostream>

using namespace std;

int sumaDz(int n) {
	int s = 1;
	for (int i = 2; i*i <= n; i++) {
		if (n % i == 0) {
			s += i;
			if (n / i != i) {
				s += n / i;
			}
		}
	}
	return s;
}

int main() {
	int a = 75;
	int sA = sumaDz(a);
	int b = sA - 1;
	int sB = sumaDz(b);
	if (sB == a + 1) {
		cout << b;
	}
	else cout << "NIE";
	
	cout << endl; system("pause"); return 0;
}