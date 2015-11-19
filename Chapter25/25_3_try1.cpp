#include <iostream>
using namespace std;

struct Message{
	Message() : str("") { }
	char str[512];
};

struct Node{
	Node() : str("") { }
	char str[384];
};

int main(){
	const int n = 10;

	cout << "sizeof(Message): " << sizeof(Message) << endl;
	cout << "sizeof(Node): " << sizeof(Node) << endl;

	// P.840
	for(int i = 0; i < n; ++i){
		Message* p = new Message();
		cout << "p: " << p << endl;
		// ...
		Node* n1 = new Node();
		cout << "n1: " << n1 << endl;
		// ...
		delete p;
		Node* n2 = new Node();
		cout << "n2: " << n2 << endl;
	}

	cout << endl;

	// P.842
	for(int i = 0; i < n; ++i){
		Node* n1 = new Node();
		Node* n2 = new Node();
		cout << "n1: " << n1 << endl;
		cout << "n2: " << n2 << endl;

		Message* p = new Message();
		cout << "p: " << p << endl;
		// ...
		delete p;
		// ...
	}
}