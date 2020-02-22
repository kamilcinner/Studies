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
	virtual string getAnimalType() const {
		return "Zwierzatko: ";
	}
	string onChain() const {
		return getAnimalType() + name;
	}
	Animal(string name) {
		this->name = name;
	}
};

class Dog : public Animal {
public:
	void bark() {
		cout << "Hau! Hau!" << endl;
	}
	void giveMeAPaw() {
		cout << "Masz lape! (:)>>" << endl;
	}
	virtual string getAnimalType() const {
		return "Pies: ";
	}
	Dog(string name) : Animal(name) {}
};

int main() {
	Dog Basta("Basta");
	Animal Kot("Kot");

	Animal& refAnimal = Kot;
	Animal& refDog = Basta;
	cout << refAnimal.onChain() << endl;
	cout << refDog.onChain() << endl << endl;

	Animal* pAnimal = &Kot;
	Animal* pDog = &Basta;
	cout << pAnimal->onChain() << endl;
	cout << pDog->onChain() << endl;

	system("pause");
	return 0;
}