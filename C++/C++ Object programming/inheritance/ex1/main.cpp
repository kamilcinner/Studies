//Kamil Cinner IIST 3.2
#include <iostream>
#include <string>

using namespace std;

class Animal {
	string name;
public:
	void setName(string name) {
		this->name = name;
	}
	const string& onChain() const {
		return name;
	}
	Animal(string name) {
		this->name = name;
	}
};

int main() {
	Animal Kot("Mruczek");
	cout << "Imie: " << Kot.onChain() << endl;
	const Animal& ref = Kot;
	cout << ref.onChain() << endl;
	system("pause");
	return 0;
}