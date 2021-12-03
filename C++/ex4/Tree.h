#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "BstNode.h"
#include "Player.h"
#include "CGPoints.h"


template <class T> class TreeNode {
private:
	BstNode<T> *root;
	int id_counter;
	int count;
public:
	//constructors and operators
	TreeNode(const TreeNode &a) {
		root = a.root;
		id_counter = a.id_counter;
		count = a.count;
	}

	TreeNode&operator=(const TreeNode &a) {
		root = a.root;
		id_counter = a.id_counter;
		count = a.count;
		return *this;
	}

	TreeNode() : root(NULL),id_counter(0),count(0) {

	}

	~TreeNode() {
		clear(root);
	}


	//functions of tree, usually will call BstNode functions
	BstNode<T> *getHead() {
		return root;
	}

	//clear out all nodes, we end up with an empty tree
	void clear(BstNode<T>* value) {
		if (value != NULL) {
			clear(value->getLeft());
			clear(value->getRight());
			if (root == value) {
				delete value;
				value = NULL;
				root = NULL;
				return;
			}
			delete value;
			value = NULL;
			count = 0;
		}
	};
	
	//insert function, calls the insert function of BstNode, main use is that it increases and gives a uniqe id to each node
	void Insert(T value) {
		BstNode<T> *node = new BstNode<T>(value, id_counter);
		if (!root) {
			root = new BstNode<T>(*node);
		}
		else {
			root->insert(&root,node);
		}
		count++;
		id_counter++;
	}

	//search a T in the tree, function calls BstNode function, requires the T to have an implemented operator==() 
	BstNode<T>* search(T value) {
		return root->search(&root, value);
	}

	//search with the node's key that was given by our tree, doesn't require implemention of operator== from T
	BstNode<T>* search(int key) {
		return root->search(&root, key);
	}

	//search a T in the tree, function calls BstNode function, requires the T to have an implemented operator==() 
	void remove(T value) {
		BstNode<T> *tmp = root->search(&root, value);
		if (tmp == NULL)
			return;
		else {
			root->remove(&root, value);
			count--;
		}
	}

	T *minimum() {
		if (!root) return NULL;
		return root->min(root);
	}

	T* maximum() {
		if (!root) return NULL;
		return root->max(root);
	}

	void print() {
		root->walk(&root,count);
	}

	int getId() {
		return id_counter;
	}
};

#endif
