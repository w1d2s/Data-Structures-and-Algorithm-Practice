#ifndef AVLTREE_H
#define AVLTREE_H
#include <algorithm>
#include <iostream>


template <typename T>
class AvlTree {
public:
	AvlTree() :root{ nullptr }{}
	AvlTree(const AvlTree & rhs) : root{ nullptr } {
		root = clone(rhs->root);
	}
	AvlTree(AvlTree && rhs){}
	AvlTree & operator=(const AvlTree & rhs){
		root = clone(rhs->root);
	}
	AvlTree & operator=(AvlTree && rhs){}
	~AvlTree() { makeEmpty(); }

	void makeEmpty() { makeEmpty(root); }
	void insert(const T & x) { insert(x, root); }
	void insert(T && x) { insert(std::move(x), root); }
	void remove(const T & x) { remove(x, root); }

	const T & findMax() const { return findMax(root)->data; }
	const T & findMin() const { return findMin(root)->data; }

	bool isEmpty() const { return root == nullptr; }
	bool contains(const T & x) const { return contains(x, root); }

	void printTree() const { printTree(root, 0); }
private:
	struct AvlNode {
		T data;
		AvlNode *left;
		AvlNode *right;
		int height;
		AvlNode(const T & _data, AvlNode * l, AvlNode * r, int h = 0):
			data{ _data }, left{ l }, right{ r }, height{ h } {}
		AvlNode(T && _data, AvlNode * l, AvlNode * r, int h = 0):
			data{ std::move(_data) }, left{ l }, right{ r }, height{ h } {}
	};

	AvlNode *root;
	static const int ALLOWED_IMBALANCE = 1;

	int height(AvlNode * t) const {
		return (t == nullptr) ? -1 : t->height;
	}
	int max(int a, int b) { return a >= b ? a : b; }

	void insert(const T & x, AvlNode * & t) {
		if (t == nullptr) {
			t = new AvlNode(x, nullptr, nullptr);
			return;
		}
		if (x > t->data) {
			insert(x, t->right);
		}
		else if (x < t->data) {
			insert(x, t->left);
		}
		else { ; }
		balance(t); // this recursion finds the deepest node imbalance on the path
	}
	void insert(T && x, AvlNode * & t) {
		if (t == nullptr) {
			t = new AvlNode(std::move(x), nullptr, nullptr);
			return;
		}
		if (x > t->data) {
			insert(std::move(x), t->right);
		}
		else if (x < t->data) {
			insert(std::move(x), t->left);
		}
		else { ; }
		balance(t); // this recursion finds the deepest node imbalance on the path}
	}
	void remove(const T & x, AvlNode * & t) {
		if (t == nullptr) {
			return;
		}
		if (x < t->data) {
			remove(x, t->left);
		}
		else if (x > t->data) {
			remove(x, t->right);
		}
		else {
			if (t->left != nullptr && t->right != nullptr) {
				AvlNode *minRightSub = findMin(t->right);
				t->data = minRightSub->data;
				remove(t->data, t->right);
			}
			else {
				AvlNode *oldNode = t;
				t = (t->left == nullptr) ? t->right : t->left;
				delete oldNode;
			}
		}
		balance(t); // find the deepest node imbalance in process of recursion
	}

	AvlNode *findMin(AvlNode * t) const {
		if (t == nullptr) {
			return nullptr;
		}
		while (t->left != nullptr) {
			t = t->left;
		}
		return t;
	}
	AvlNode *findMax(AvlNode * t) const {
		if (t == nullptr) {
			return nullptr;
		}
		while (t->right != nullptr) {
			t = t->right;
		}
		return t;
	}

	bool contains(const T & x, AvlNode * t) const {
		if (t == nullptr) {
			return false;
		}
		if (x > t->data) {
			return contains(x, t->right);
		}
		else if (x < t->data) {
			return contains(x, t->left);
		}
		else {
			return true;
		}
	}

	void balance(AvlNode * & t) {
		if (t == nullptr) {
			return;
		}
		if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
			if (height(t->left->left) >= height(t->left->right)) {
				rotateWithLeftChild(t);
			}
			else {
				doubleWithLeftChild(t);
			}
		}
		else {
			if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
				if (height(t->right->right) >= height(t->right->left)) {
					rotateWithRightChild(t);
				}
				else {
					doubleWithRightChild(t);
				}
			}
		}
		t->height = max(height(t->left), height(t->right)) + 1;
	}

	void rotateWithLeftChild(AvlNode * & k2) {
		if (k2 == nullptr) {
			return;
		}
		AvlNode *k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), height(k2)) + 1;
		k2 = k1;
	}
	void rotateWithRightChild(AvlNode * & k2) {
		if (k2 == nullptr) {
			return;
		}
		AvlNode *k1 = k2->right;
		k2->right = k1->left;
		k1->left = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->right), height(k2)) + 1;
		k2 = k1;
	}
	void doubleWithLeftChild(AvlNode * & k3) {
		//AvlNode *k1 = k3->left;  // fatal error: k1 is changed but k3->left not changed !!!
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}
	void doubleWithRightChild(AvlNode * & k3) {
		//AvlNode *k1 = k3->right;
		rotateWithLeftChild(k3->right);
		rotateWithRightChild(k3);
	}

	AvlNode *clone(AvlNode * t) const {
		if (t == nullptr) {
			return nullptr;
		}
		AvlNode *tmp = new AvlNode(t->data, clone(t->left), clone(t->right), t->height());
		return tmp;
	}

	void makeEmpty(AvlNode * t) {
		if (t != nullptr) {
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}

	void printTree(AvlNode * t, int depth) const {
		if (t == nullptr) {
			return;
		}
		for (int i = 0; i < depth; ++i)
			std::cout << "--";
		std::cout << t->data << std::endl;
		printTree(t->left, depth + 1);
		printTree(t->right, depth + 1);
	}
};


#endif
