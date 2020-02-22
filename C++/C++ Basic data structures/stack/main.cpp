// The author of this program is Kamil Cinner
#include <iostream>

using namespace std;

class node {
  public:
	int data;
	node *next;

	node(int x) {
		data = x;
		next = NULL;
	}
};

class Stack {
  public:
	  node * top;

	  void push(node *n) {
		  n->next = top;
		  top = n;
	  }
	  void pop(){
		  if (top == NULL) return;
		  node* n = top;
		  top = top->next;
		  delete(n);
	  }
	  bool isEmpty() {
		  if (top == NULL) return true;
		  else return false;
	  }

	  Stack() {
		  top = NULL;
	  }
};

int main() {
	Stack S;
	int choice;
	int number = 0;
	node* supi = new node(number);
	bool switcher;
	do {
		switcher = true;
		cout << "1.Put element on stack" << endl;
		cout << "2.Remove element from stack" << endl;
		cout << "3.Print stack" << endl;
		cout << "4.Exit program" << endl;
		cout << ": ";
		cin >> choice;
		switch (choice) {
		case 1: {
			cout << "Enter number: ";
			cin >> number;
			node* supi = new node(number);
			S.push(supi);
			break;
			}
		case 2: {
			S.pop();
			break;
		}
		case 3: {
			Stack S2;
			while (!S.isEmpty()) {
				number = S.top->data;
				node* supi = new node(number);
				S2.push(supi);
				S.pop();
				cout << number << endl;
			}
			while (!S2.isEmpty()) {
				number = S2.top->data;
				node* supi = new node(number);
				S.push(supi);
				S2.pop();
			}
			break;
		}
		case 4: {
			switcher = false;
			break;
		}
		default: {
			cout << "Inavild data provided!" << endl;
		}
		}
	} while (switcher);
	delete[] supi;

	return 0;
}