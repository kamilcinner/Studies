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
    node *previous;

    node(int x) {
        data = x;
        next = NULL;
        previous = NULL;
    }
};

class TwoWayLinkedList {
  public:
    node *head;
	node *tail;

	node* searchNode(int k) {
		node *ptr = head;
		if (head == NULL) return NULL;
		while (ptr != tail && ptr->data != k) {
			ptr = ptr->next;
		}
		if (ptr->data == k) return ptr;
		else return NULL;
	}
	node* searchNodePosition(int k) {
		node *ptr = head;
		if (head == NULL) return NULL;
		while (ptr != tail && k > 1) {
			ptr = ptr->next;
			k--;
		}
		if (k == 1) return ptr;
		else return NULL;
	}
	void add(node *n, node *ptr) {
		ptr->previous->next = n;
		n->next = ptr;
		n->previous = ptr->previous;
		ptr->previous = n;
	}
	void addOver(node *n) {
		n->next = NULL;
		n->previous = NULL;
		head = tail = n;
	}
	void addAtFront(node *n) {
		if (tail == NULL) {
			addOver(n);
		}
		else {
			head->previous = n;
			n->next = head;
			n->previous = NULL;
			head = n;
		}
	}
	void addAtEnd(node *n) {
		if (head == NULL) {
			addOver(n);
		}
		else {
			tail->next = n;
			n->previous = tail;
			n->next = NULL;
			tail = n;
		}
	}
	
	void addNode(node *n, int var, string switcher) {
		node *ptr;
		if (switcher == "element") {
			ptr = searchNode(var);
			if (ptr != NULL) ptr = ptr->next;
		}
		else if (switcher == "position") {
			ptr = searchNodePosition(var);
		}

		if (ptr == head) {
			addAtFront(n);
		}
		else if (ptr == NULL) {
			addAtEnd(n);
		}
		else {
			add(n, ptr);
		}
	}
    
    void deleteNode(int var, string switcher) {
		node *n;
		if (switcher == "element") {
			n = searchNode(var);
		}
		else if (switcher == "position") {
			n = searchNodePosition(var);
		}

		if (n == NULL) return;
        node *ptr = head;
        if(ptr == n) {
            head = n->next;
			head->previous = NULL;
        }
		else if (n == tail) {
			n->previous->next = NULL;
		}
        else {
            while(ptr->next != n) {
                ptr = ptr->next;
            }
            ptr->next = n->next;
			n->next->previous = ptr;
        }
		delete(n);
    }

	int searchNodeIndex(int k) {
		node *ptr = head;
		int z = 1;
		while (ptr != tail && ptr->data != k) {
			ptr = ptr->next;
			z++;
		}
		if (ptr->data == k) { return z; }
		else { return 0; }
	}

    void printListFromBeginning() {
        node *ptr = head;
        while(ptr != NULL) {
			cout << ptr->data << " -> ";
            ptr = ptr->next;
        }
    }
	void printListFromEnd() {
		node *ptr = tail;
		while (ptr != NULL) {
			cout << ptr->data << " -> ";
			ptr = ptr->previous;
		}
	}

    TwoWayLinkedList() {
        head = NULL;
		tail = NULL;
    }
};

int main()
{
	TwoWayLinkedList List;
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
		cout<<"1.Add new element on specified position"<<endl;
        cout<<"2.Add new element behind specified element" << endl;
        cout<<"3.Remove element from specified position"<<endl;
        cout<<"4.Remove element with specified value"<<endl;
        cout<<"5.Find element"<<endl;
        cout<<"6.Print the list from the front"<<endl;
        cout<<"7.Print the list from the back"<<endl;
        cout<<"8.Exit program"<<endl;
        cout<<": ";
        cin>>choice;
		switch (choice) {
		case 1: {
			cout << "Enter position: ";
			cin >> poselem;
			cout << "Enter value: ";
			cin >> number;
			node* fair = new node(number);
			List.addNode(fair, poselem, "position");
			break;
		}
		case 2: {
			cout << "Enter element: ";
			cin >> poselem;
			cout << "Enter value: ";
			cin >> number;
			node* fair = new node(number);
			List.addNode(fair, poselem, "element");
			break;
		}
		case 3: {
			cout << "Enter position: ";
			cin >> poselem;
			List.deleteNode(poselem, "position");
			break;
		}
		case 4: {
			cout << "Enter element: ";
			cin >> poselem;
			List.deleteNode(poselem, "element");
			break;
		}
		case 5: {
			cout << "Enter element: ";
			cin >> number;
			var = List.searchNodeIndex(number);
			if (var != 0) {
				cout << "Found that element on position " << var << "\n";
			}
			else {
				cout << "No such element found\n";
			}
			break;
		}
		case 6: {
			List.printListFromBeginning();
			cout << endl;
			break;
		}
		case 7: {
			List.printListFromEnd();
			cout << endl;
			break;
		}
		case 8: {
			switcher = false;
			break;
		}
		default: cout << "Invalid data provided!" << endl;
        }
	} while (switcher);

	delete[] fair;

    return 0;
}
