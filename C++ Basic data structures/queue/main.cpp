// The author of this program is Kamil Cinner.
#include <iostream>
#include <stdlib.h>

using namespace std;

class node
{
public:
	int data;
    node* next;
    node(int x)
    {
        data = x;
        next = NULL;
    }
};

class Queue
{
public:
    node* front;
    node* back;

    void enqueue(node* n)
    {
        if(back == NULL) 
        {
            front = back = n;
        }
        else
        {
            back->next = n;
            back = n;
        }
    }
    void dequeue()
    {
        if(front == NULL)
            return;

        node* n = front;
        front = front->next;
        if(front == NULL)
            back = NULL;

        delete(n);
    }
	bool isEmpty()
    {
		if (front == NULL) return true;
		else return false;
	}
    /*void print() {
        node* ptr = front;
        while(ptr != NULL) {
            cout << ptr->data << " -> ";
			ptr = ptr->next;
        }
    }*/

    Queue()
    {
        front = back = NULL;
    }
};

int main()
{
	Queue Q;
	int number = 0;
	int choice;
    bool p = true;
	node* var = new node(number);
    do 
    {
        cout << "1. Create empty queue\n2. Add element to queue\n3. Remove element from queue\n4. Print queue\n5. Exit\n: ";
		cin >> choice;
        switch(choice)
        {
		case 1: {
			while(!Q.isEmpty())
            {
				Q.dequeue();
			}
			break;
		}
        case 2:
        {
			cout << "Enter number: ";
			cin >> number;
			node* var = new node(number);
			Q.enqueue(var);
            break;
        }
        case 3:
        { 
			Q.dequeue();
			break;
		}
		/*case 4: {
			system("cls");
			cout << "Queue content:" << endl;
			cout << "-----------------------------------" << endl;
			Q.print();
			cout << endl << "-----------------------------------" << endl;
			cout << endl;
			system("pause");
			break;
		}*/
		case 4:
        {
			Queue Q2;
			while(!Q.isEmpty())
            {
				number = Q.front->data;
				node* var = new node(number);
				Q2.enqueue(var);
				Q.dequeue();
			}
			while(!Q2.isEmpty())
            {
				number = Q2.front->data;
				node* var = new node(number);
				Q.enqueue(var);
				Q2.dequeue();
				cout << number << " -> ";
			}
			cout << endl;
			break;
		}
        case 5: p = false; break;
        default: cout << "Invalid data provided!" << endl;
        }
    } while(p);

	delete [] var;

    return 0;
}
