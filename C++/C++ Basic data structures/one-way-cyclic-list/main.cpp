// The author of this program is Kamil Cinner.
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <ctime>

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

class CyclicLinkedList {
  public:
    node *point;

	node* searchNode(int k) {
		node *ptr = point;
		if (point == NULL) return NULL;
		/*while (ptr != point && ptr->data != k) {
			ptr = ptr->next;
		}*/
		if (ptr->data != k) {
			do {
				ptr = ptr->next;
			} while (ptr != point && ptr->data != k);
		}
		if (ptr->data == k) return ptr;
		else return NULL;
	}

	void add(node *n, node *ptr) {
		node* ptr2 = point;
		while (ptr2->next != ptr) {
			ptr2 = ptr2->next;
		}
		ptr2->next = n;
		n->next = ptr;
	}

	void addOver(node *n) {
		n->next = n;
		point = n;
	}
	
	void addNode(node *n, int var) {
		if (point == NULL) {
			addOver(n);
		}
		else {
			node *ptr = searchNode(var);
			if (ptr != NULL) ptr = ptr->next;
			add(n, ptr);
		}
	}
    
    void deleteNode(int var) {
		node *n = searchNode(var);
	
		if (n == NULL) return;
        node *ptr = point;
        if(ptr == n) {
            point = n->next;
        }
		else {
			while (ptr->next != n) {
				ptr = ptr->next;
			}
			ptr->next = n->next;
		}
		delete(n);
    }

    void printList() {
        node *ptr = point;
		if (ptr != NULL) {
			do {
				cout << ptr->data << " -> ";
				ptr = ptr->next;
			} while (ptr != point);
		}
		/*while (ptr != NULL && ptr->next != point) {
			cout << ptr->data << " -> ";
			ptr = ptr->next;
		}*/
    }

	void isThereThatNode(int k) {
		node *ptr = point;
		if (point == NULL) {
			cout << "No such element found" << endl;
			return;
		}
		while (ptr != point->next && ptr->data != k) {
			ptr = ptr->next;
		}
		if (ptr->data == k) cout << "Found that element" << endl;
		else cout << "No such element found" << endl;
	}

    CyclicLinkedList() {
        point = NULL;
    }
};

int main()
{
	CyclicLinkedList List;
	int number = 0;
	int poselem;
    int choice;
    bool switcher;
	int var;
	node* fair = new node(number);
	//TEST
	/*srand(time(NULL));
	for (int i = 0;i < 10;i++) {
		number = rand() % 1001;
		node* fair = new node(number);
		List.addNode(fair, 999, "position");
	}*/
	//TEST
    do {
        switcher = true;
        cout<<"1.Add new element behind specific element" << endl;
        cout<<"2.Remove element with specified value"<<endl;
        cout<<"3.Find element"<<endl;
        cout<<"4.Print list"<<endl;
        cout<<"5.Exit program"<<endl;
        cout<<": ";
        cin>>choice;
		switch (choice) {
		case 1: {
			cout << "Enter element: ";
			cin >> poselem;
			cout << "Enter value: ";
			cin >> number;
			node* fair = new node(number);
			List.addNode(fair, poselem);
			break;
		}
		case 2: {
			cout << "Enter element: ";
			cin >> poselem;
			List.deleteNode(poselem);
			break;
		}
		case 3: {
			cout << "Enter element: ";
			cin >> number;
			List.isThereThatNode(number);
			break;
		}
		case 4: {
			List.printList();
			cout << endl;
			break;
		}
		case 5: {
			switcher = false;
			break;
		}
		default: cout << "Invalid data provided!" << endl;
        }
	} while (switcher);

	delete[] fair;

    return 0;
}
