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
	virtual const string getAnimalType() {
		return "Zwierzatko: ";
	}
	const string onChain() {
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
	const string getAnimalType() {
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
	cout << pDog->onChain() << endl << endl;

	Animal& refD = Basta;
	Animal* pD = &refD;
	Dog* pD2 = dynamic_cast<Dog*>(pD);
	cout << "Is it working" << pD2->onChain() << endl;

	//Dog* pDog2 = dynamic_cast<Dog*>(pAnimal);
	//cout << pDog2 << endl;
	Dog* pDog3 = dynamic_cast<Dog*>(pDog);
	//cout << pDog2->onChain() << endl;
	cout << pDog3->onChain() << endl << endl;

	//Dog& refDog2 = dynamic_cast<Dog&>(refAnimal);
	//cout << &refDog2 << endl;
	Dog& refDog3 = dynamic_cast<Dog&>(refDog);
	//cout << refDog2.onChain() << endl;
	cout << refDog3.onChain() << endl << endl;

	system("pause");
	return 0;
}