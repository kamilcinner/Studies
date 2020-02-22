#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
	stringstream strumien;
	strumien << "10 20 30" << " napis";
	cout << strumien.str() << endl;
	int a, b, c;
	strumien >> a >> b >> c;
	cout << a << " " << b << " " << c << endl;
	string napis;
	strumien >> napis;
	cout << napis << endl;
	system("pause");
	return 0;
}