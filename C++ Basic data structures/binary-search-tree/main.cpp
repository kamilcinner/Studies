// The author of this program is Kamil Cinner.
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Node {
  public:
	  int data;
	  Node *left;
	  Node *right;
	  Node(int data) {
		  this->data = data;
		  this->left = NULL;
		  this->right = NULL;
	  }
};

Node* search(Node* root, int data) {
	if (root == NULL) {
		cout << "No such element found" << endl;
		return NULL;
	}
	if (root->data == data) {
		cout << "Found that element" << endl;
		return root;
	}
	if (root->data < data)
		return search(root->right, data);
	else
		return search(root->left, data);
}

void insert(Node* &root, int data) {
	if (root == NULL) {
		root = new Node(data);
	}
	else if (data <= root->data) {
		if (root->left != NULL)
			insert(root->left, data);
		else
			root->left = new Node(data);
	}
	else if (data > root->data) {
		if (root->right != NULL)
			insert(root->right, data);
		else
			root->right = new Node(data);
	}
}

void dNode(Node* &son) {
	if (son->left == NULL && son->right == NULL) { // leaf
		son = NULL;
	}
	else if (son->left == NULL) { // left node empty
		son = son->right;
	}
	else if (son->right == NULL) { // right node empty
		son = son->left;
	}
	else { // both nodes filled
		Node* son2 = son->left;
		Node* son3 = son2;
		while (son3->right != NULL) {
			son2 = son3;
			son3 = son3->right;
		}
		if (son2 != son3) { // ...-> son-> ...-> son2-> son3
			if (son3->left == NULL) {
				son2->right = NULL;
			}
			else {
				son2->right = son3->left;
			}
		}
		else { // ...-> son-> son2==son3
			if (son3->left == NULL) {
				son->left = NULL;
			}
			else {
				son->left = son3->left;
			}
		}
		son3->left = son->left;
		son3->right = son->right;
		son = son3;
	}
}

Node* deleteNode(Node* &root, int data) {
	if (root == NULL)
		return NULL;
	if (root->left != NULL && root->left->data == data) {
		Node *son = root->left;
		dNode(son);
		delete(root->left);
		root->left = son;
	}
	else if (root->right != NULL && root->right->data == data) {
		Node *son = root->right;
		dNode(son);
		delete(root->right);
		root->right = son;
	}
	else if (root->data == data) {
		Node *son = root;
		dNode(son);
		delete(root);
		root = son;
	}
	else if (root->data < data)
		return deleteNode(root->right, data);
	else
		return deleteNode(root->left, data);	
}

void inorder(Node* root) {
	if (root == NULL) {
		return;
	}
	inorder(root->left);
	cout << root->data << " , ";
	inorder(root->right);
}

int main() {
	Node *root = NULL;
	bool switcher;
	int choice;
	int number;
	//TestStart
	/*srand(time(NULL));
	for (int i = 0;i < 20;i++) {
		number = rand() % 100 + 1;
		insert(root, number);
	}*/
	//TestEnd
	do {
		switcher = true;
		cout << "1.Add new element to the tree" << endl;
		cout << "2.Browse tree" << endl;
		cout << "3.Find element" << endl;
		cout << "4.Remove element from the tree" << endl;
		cout << "5.Exit program" << endl;
		cout << ": ";
		cin >> choice;
		switch (choice) {
		case 1: {
			cout << "Enter value: ";
			cin >> number;
			insert(root, number);
			break;
		}
		case 2: {
			inorder(root);
			cout << endl;
			break;
		}
		case 3: {
			cout << "Enter element: ";
			cin >> number;
			search(root, number);
			break;
		}
		case 4: {
			cout << "Enter the element to remove: ";
			cin >> number;
			deleteNode(root, number);
			//Test Start
			/*for (int i = 0;i < 30;i++) {
				number = rand() % 100 + 1;
				deleteNode(root, number);
			}*/
			//Test End
			break;
		}
		case 5: {
			switcher = false;
			break;
		}
		default: cout << "Invalid data provided!" << endl;
		}
	} while (switcher);

	delete(root);
	return 0;
}