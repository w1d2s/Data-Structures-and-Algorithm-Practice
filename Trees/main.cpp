#include <iostream>
#include "BST.h"
#include "AVLTree.h"

using namespace std;

int main() {
	int r;
	//BinarySearchTree<int> bst;
	AvlTree<int> avl;
	avl.insert(3);
	avl.insert(2);
	avl.insert(1);
	avl.insert(4);
	avl.insert(5);
	avl.insert(6);
	avl.insert(7);
	avl.printTree();
	cout << "=======" << endl;
	for (int i = 16; i >= 10; i--)
		avl.insert(i);
	avl.printTree();
	cout << "=======" << endl;
	avl.insert(8);
	avl.insert(9);
	avl.printTree();
	while (true) {
		int a;
		cin >> a;
		if (avl.contains(a))
			cout << "contains " << a << endl;
		else
			cout << "doesnt contain " << a << endl;
	}
	cin >> r;
	cout << "Hello World!" << endl;
	return 0;
}