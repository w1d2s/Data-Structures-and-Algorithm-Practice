#ifndef BST_H
#define BST_H
#include <algorithm>
#include <iostream>

template <typename T>
class BinarySearchTree {
public:
	BinarySearchTree() : root{ nullptr }{}
	BinarySearchTree(const BinarySearchTree & rhs) :root{ nullptr } {
		root = clone(rhs.root);
	}
	BinarySearchTree(BinarySearchTree && rhs){}
	~BinarySearchTree() { makeEmpty(); }

	const T & findMin() const { return *findMin(root); }
	const T & findMax() const { return *findMax(root); }
	bool contains(const T & x) const { return contains(x, root); }
	bool isEmpty() const { return (root == nullptr); }
	void printTree() const {
		printTree(root, 0);
	}

	void makeEmpty() { makeEmpty(root); }
	void insert(const T & x) { insert(x, root); }
	void insert(T && x) { insert(std::move(x), root); }
	void remove(const T & x) { remove(x, root); }

	BinarySearchTree & operator=(const BinarySearchTree & rhs) {
		root = clone(rhs.root);
	}
	BinarySearchTree & operator=(BinarySearchTree && rhs){}
	
private:
	struct TreeNode {
		T data;
		TreeNode *left;
		TreeNode *right;
		TreeNode(const T & _data, TreeNode *_left, TreeNode *_right) :
			data{ _data }, left{ _left }, right{ _right } {}
		TreeNode(T && _data, TreeNode *_left, TreeNode *_right) :
			data{ std::move(_data) }, left{ _left }, right{ _right } {}
		TreeNode() {
			left = right = nullptr;
		}
	};

	TreeNode *root;

	void insert(const T & x, TreeNode * & t) {
		if (t == nullptr) {
			t = new TreeNode(x, nullptr, nullptr);
			return;
		}
		if (x > t->data) {
			insert(x, t->right);
		}
		else if (x < t->data) {
			insert(x, t->left);
		}
		return;
	}
	void insert(T && x, TreeNode * & t) {
		if (t == nullptr) {
			t = new TreeNode(std::move(x), nullptr, nullptr);
			return;
		}
		if (x > t->data) {
			insert(std::move(x), t->right);
		}
		else if (x < t->data) {
			insert(std::move(x), t->left);
		}
		return;
	}

	void remove(const T & x, TreeNode * & t) {
		if (t == nullptr) {
			return;
		}
		if (x > t->data) {
			remove(x, t->right);
		}
		else if (x < t->data) {
			remove(x, t->left);
		}
		else {
			if (t->left != nullptr && t->right != nullptr) {
				// t has 2 children, find min value of t's right subtree and exchange with t, then delete min value;
				TreeNode *minVal = findMin(t->right);
				t->data = minVal->data;
				remove(t->data, t->right);
			}
			else {
				// t has at most 1 child
				TreeNode *oldNode = t;
				t = (t->left == nullptr) ? t->right : t->left;
				delete oldNode;
			}
		}
		return;
	}

	TreeNode *findMax(TreeNode * t) const {
		if (t == nullptr) {
			return nullptr;
		}
		while (t->right != nullptr) {
			t = t->right;
		}
		return t;
	}
	TreeNode *findMin(TreeNode * t) const {
		if (t == nullptr) {
			return nullptr;
		}
		while (t->left != nullptr) {
			t = t->left;
		}
		return t;
	}

	bool contains(const T & x, TreeNode * t) const {
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

	void makeEmpty(TreeNode * & t) {
		if (t != nullptr) {
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}

	TreeNode *clone(TreeNode * t) const {
		if (t == nullptr) {
			return nullptr;
		}
		return new TreeNode{ t->data, clone(t->left), clone(t->right) };
	}

	void printTree(TreeNode * t, int depth) const {
		if (t == nullptr) {
			return;
		}
		for (int i = 0; i < depth; i++)
			std::cout << "--";
		std::cout << t->data << std::endl;
		printTree(t->left, depth + 1);
		printTree(t->right, depth + 1);
	}
};

#endif
