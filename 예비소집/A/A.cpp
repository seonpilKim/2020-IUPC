#include <iostream>

using namespace std;

class Node {
public:
	int N;
	Node* next;

	Node(int N) {
		this->N = N;
		this->next = NULL;
	}
};

class LinkedList {
public:
	Node* head;
	Node* tail;
	int size;

	LinkedList() {
		this->head = NULL;
		this->tail = NULL;
		this->size = 0;
	}

	void insert(int n) {
		Node* newNode = new Node(n);
		if (this->size == 0) this->head = this->tail = newNode;
		else {
			this->tail->next = newNode;
			this->tail = newNode;
		}
		this->size++;
	}

	void merge() {
		Node* ptrNode = this->head;
		while (true) {
			if (ptrNode->next == this->tail) {
				ptrNode->N = (ptrNode->N + ptrNode->next->N) % 10;
				Node* delNode = this->tail;
				this->tail = ptrNode;
				delete delNode;
				this->size--;
				break;
			}
			ptrNode->N = (ptrNode->N + ptrNode->next->N) % 10;
			ptrNode = ptrNode->next;
		}
		if (this->size > 2) merge();
		else if (this->size == 2) cout << (this->head->N * 10) + this->tail->N << "%";
	}
};

int stroke(char);

int main() {
	int N, M;
	char* name1, * name2;
	LinkedList list;

	cin >> N >> M;

	name1 = new char[N];
	name2 = new char[M];

	for (int i = 0; i < N; i++) {
		cin >> name1[i];
	}
	name1[N] = NULL;

	for (int i = 0; i < M; i++) {
		cin >> name2[i];
	}
	name2[M] = NULL;

	for (int i = 0, ptr1 = 0, ptr2 = 0; i < N + M; i++) {
		if (i % 2 == 0 && name1[ptr1] != NULL || name2[ptr2] == NULL) list.insert(stroke(name1[ptr1++]));
		else if(i%2 != 0 && name2[ptr2] != NULL || name1[ptr1] == NULL) list.insert(stroke(name2[ptr2++]));
	}

	list.merge();

	return 0;
}

int stroke(char c) {
	if (c == 'A' || c == 'F' || c == 'H' || c == 'K' || c == 'M') return 3;
	else if (c == 'E') return 4;
	else if (c == 'B' || c == 'D' || c == 'N' || c == 'P' || c == 'Q' || c == 'R' || c == 'T'
		|| c == 'X' || c == 'Y') return 2;
	else if (c == 'C' || c == 'G' || c == 'I' || c == 'J' || c == 'L' || c == 'O' || c == 'S'
		|| c == 'U' || c == 'V' || c == 'W' || c == 'Z') return 1;
}