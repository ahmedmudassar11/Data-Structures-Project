#include<iostream>
using namespace std;


struct node {
	int frequency;
	char ch;
	node* left, * right, * next;
	node() {
		frequency = 0;
		ch = ' ';
		left = NULL; right = NULL; next = NULL;
	}
	node(node* given) {
		this->ch = given->ch;
		this->frequency = given->frequency;
		this->left = given->left;
		this->right = given->right;
		this->next = given->next;

	}
};

struct queue {
	node* front;
	int size;
	queue() {
		size = 0;
		front = NULL;
	}
	void eQueue(node* given) {
		node* temp = front;
		if (temp) {
			while (temp->next) {
				temp = temp->next;
			}

			temp->next = new node;
			temp->next->ch = given->ch;
			temp->next->frequency = given->frequency;
			temp->next->left = given->left;
			temp->next->right = given->right;

		}
		else {
			front = new node;
			front->ch = given->ch;
			front->frequency = given->frequency;
			front->left = given->left;
			front->right = given->right;
		}
		size++;
	}
	node* minDQueue() {
		queueSort();
		node* temp = new node;
		temp->ch = front->ch;
		temp->frequency = front->frequency;
		temp->left = front->left;
		temp->right = front->right;

		front = front->next;
		size--;
		return temp;

	}
	void display() {
		node* temp = front;

		while (temp) {
			cout << temp->frequency << endl;
			temp = temp->next;
		}
	}

	void queueSort() {
		node* temp = front;
		node mini = new node(front);
		while (temp) {
			if (mini.frequency > temp->frequency) {
				mini.ch = temp->ch;
				mini.frequency = temp->frequency;
				mini.left = temp->left;
				mini.right = temp->right;
			}
			temp = temp->next;
		}
		temp = front;
		while (temp) {
			if (mini.ch == temp->ch && mini.frequency == temp->frequency) {
				temp->ch = front->ch;
				temp->frequency = front->frequency;
				temp->left = front->left;
				temp->right = front->right;

				front->ch = mini.ch;
				front->frequency = mini.frequency;
				front->left = mini.left;
				front->right = mini.right;
				break;
			}
			temp = temp->next;
		}
	}
};
void createHuffTree(node& tree, queue q) {
	node* hNode = new node;
	int size = q.size;

	while (size > 0) {
		if (size == 1) {
			tree = q.minDQueue();
		}
		else {
			hNode->left = q.minDQueue();
			hNode->right = q.minDQueue();
			hNode->frequency = hNode->right->frequency + hNode->left->frequency;
			q.eQueue(hNode);
		}
		size--;
	}

}

void createHuffTable(string* huffTable, string code, int counter, node* root) {
	if (root->left) {
		code[counter] = '0';
		createHuffTable(huffTable, code, counter + 1, root->left);
	}
	if (root->right) {
		code[counter] = '1';
		createHuffTable(huffTable, code, counter + 1, root->right);

	}
	if (!root->left && !root->right) {
		string pureCode = "";
		for (int i = 0; i < counter; i++) { pureCode += code[i]; }
		cout << root->ch << "\t" << pureCode << endl;
		huffTable[root->ch] = pureCode;
	}
}
void traversal(node* root) {

	if (!root) { return; }
	cout << root->frequency << root->ch << endl;
	traversal(root->left);
	traversal(root->right);
}

int main() {
	queue q;
	node* n1 = new node, * n2 = new node, * n3 = new node, * n4 = new node, * n5 = new node, * n6 = new node;
	n1->frequency = 50; n1->ch = 'a';
	n2->frequency = 10; n2->ch = 'b';
	n3->frequency = 30; n3->ch = 'c';
	n4->frequency = 5; n4->ch = 'd';
	n5->frequency = 3; n5->ch = 'e';
	n6->frequency = 2; n6->ch = 'f';

	q.eQueue(n2);
	q.eQueue(n3);
	q.eQueue(n1);
	q.eQueue(n4);
	q.eQueue(n5);
	q.eQueue(n6);
	string* huffTable = new string[256];
	node* treeRoot = new node;
	char* code = new char;
	createHuffTree(*treeRoot, q);
	createHuffTable(huffTable, code, 0, treeRoot);

}