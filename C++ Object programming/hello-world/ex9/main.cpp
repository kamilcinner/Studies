#include <iostream>

using namespace std;

void funkcja(int &a) {
	unsigned int adr = reinterpret_cast<unsigned int>(&a);
	cout << "adres (dziesietnie): " << adr << endl;
}

int main() {
	int i = 10;
	const int &r = i;
	cout << "adres (dziesietnie): " << &i << endl;
	funkcja(const_cast<int &>(r));
	int j = 15;
	cout << "i=" << i << " j=" << j << " a i/j=" << static_cast<float>(i) / static_cast<float>(j) << endl;

	system("pause");
	return 0;
}