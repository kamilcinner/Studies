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
	Animal(string name = "Noname") {
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

class AnimalShelter {
	Animal* Animals[100];
public:
	/*int index;
	void addAnimal(Animal* A) {
		Animals[index] = *A;
		index++;
	}*/
	Animal* getAnimal(int index) {
		return Animals[index];
	}
	AnimalShelter(Animal* A[], int size) {
		//index = 0;
		//Animals = new Animal[100];
		for (int i = 0; i < size; i++) {
			Animals[i] = A[i];
		}
	}
};

int main() {
	//AnimalShelter* AS = new AnimalShelter;

	Dog Basta("Basta");
	Dog Rufus("Rufus");
	Dog Szarik("Szarik");
	Dog Aron("Aron");

	/*AS->addAnimal(Basta);
	AS->addAnimal(Rufus);
	AS->addAnimal(Szarik);
	AS->addAnimal(Aron);*/

	Animal* pBasta = &Basta;
	Animal* pRufus = &Rufus;

	/*AS->addAnimal(pBasta);
	AS->addAnimal(pRufus);*/

	Animal* A[2] = { pBasta,pRufus };
	AnimalShelter AS(A, 2);

	Dog* dogee;

	try {
		dogee = dynamic_cast<Dog*>(AS.getAnimal(0));
		cout << dogee->onChain() << endl;
		dogee->bark();
	} catch(bad_alloc &badA) {
		cout << badA.what() << endl;
	}

	//Animal* pointer = NULL;

	//for (int i = 0; i <= AS->index; i++) {
	//	pointer = dynamic_cast<Dog*>(AS->getAnimal(i)); //tutaj robi sie NULL :///
	//	if (pointer != NULL) cout << pointer->onChain() << endl;
	//	//cout << dynamic_cast<Dog*>(AS->getAnimal(i))->onChain() << endl; //to nie zadziala bo NULL
	//	dynamic_cast<Dog*>(AS->getAnimal(i))->bark(); //tutaj odziwo dziala chociaz ma byc NULL XD chyba
	//}
	//pointer = NULL; delete pointer; AS = NULL; delete AS;
	dogee = NULL; delete dogee;
	system("pause");
	return 0;
}