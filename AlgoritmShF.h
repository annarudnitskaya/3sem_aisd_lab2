#pragma once
#include "List.h"
#include "queue.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// class shannonfano implements the Shannon-Fano algorithm, using associative map (Red Black Tree)
class shannonfano {
private:

	struct Node {
		char symb;
		int value;
		Node* parent;
		Node* left;
		Node* right;
		bool isRed;
		queue code;
	};
	typedef Node* NodePtr;
	NodePtr root;
	NodePtr NIL;
	List sorted;

	void initializeNULLNode(NodePtr node, NodePtr parent) {
		node->symb = 0;
		node->value = 0;
		node->parent = parent;
		node->left = nullptr;
		node->right = nullptr;
		node->isRed = false;
	}

	void preOrderHelper(NodePtr node) {
		if (node != NIL) {
			cout << node->symb << " ";
			cout << node->value << " ";
			preOrderHelper(node->left);
			preOrderHelper(node->right);
		}
	}

	void inOrderHelper(NodePtr node, bool keys, bool values) {
		if (node != NIL) {
			inOrderHelper(node->left, keys, values);
			if (keys == true) {
				cout << "For symbol ";
				if (node->symb == ' ')
					cout << "_" << " the code is ";
				else
					cout << node->symb << " the code is ";
				node->code.show_queue();
				cout << endl;
			}

			if (values == true)
				cout << node->value << endl;
			inOrderHelper(node->right, keys, values);
		}
	}

	void postOrderHelper(NodePtr node) {
		if (node != NIL) {
			postOrderHelper(node->left);
			postOrderHelper(node->right);
			cout << node->symb << " ";
			cout << node->value << " ";
		}
	}

	NodePtr searchTreeHelper(NodePtr node, char key) {
		if (node == NIL || key == node->symb) {
			if (node == NIL) {
				//cout << "The tree does not contain key " << key << endl;
				return node;
			}
			else {
				//cout << "The tree does contain " << key << ". Its value is " << node->value << endl;
				return node;
			}
		}

		if (key < node->symb) {
			return this->searchTreeHelper(node->left, key);
		}
		return this->searchTreeHelper(node->right, key);
	}

	// fix the rb tree modified by the delete operation
	void fixDelete(NodePtr instead_scnd) {
		NodePtr sibling;
		while (instead_scnd != root && instead_scnd->isRed == false) {
			if (instead_scnd == instead_scnd->parent->left) {
				sibling = instead_scnd->parent->right;
				if (sibling->isRed == true) {
					// case 3.1
					sibling->isRed = false;
					instead_scnd->parent->isRed = true;
					leftRotate(instead_scnd->parent);
					sibling = instead_scnd->parent->right;
				}

				if (sibling->left->isRed == false && sibling->right->isRed == false) {
					// case 3.2
					sibling->isRed = true;
					instead_scnd = instead_scnd->parent;
				}
				else {
					if (sibling->right->isRed == false) {
						// case 3.3
						sibling->left->isRed = false;
						sibling->isRed = true;
						rightRotate(sibling);
						sibling = instead_scnd->parent->right;
					}

					// case 3.4
					sibling->isRed = instead_scnd->parent->isRed;
					instead_scnd->parent->isRed = false;
					sibling->right->isRed = false;
					leftRotate(instead_scnd->parent);
					instead_scnd = root;
				}
			}
			else {
				sibling = instead_scnd->parent->left;
				if (sibling->isRed == true) {
					// case 3.1
					sibling->isRed = false;
					instead_scnd->parent->isRed = true;
					rightRotate(instead_scnd->parent);
					sibling = instead_scnd->parent->left;
				}

				if (sibling->left->isRed == false && sibling->right->isRed == false) {
					// case 3.2
					sibling->isRed = true;
					instead_scnd = instead_scnd->parent;
				}
				else {
					if (sibling->left->isRed == false) {
						// case 3.3
						sibling->right->isRed = false;
						sibling->isRed = true;
						leftRotate(sibling);
						sibling = instead_scnd->parent->left;
					}

					// case 3.4
					sibling->isRed = instead_scnd->parent->isRed;
					instead_scnd->parent->isRed = false;
					sibling->left->isRed = false;
					rightRotate(instead_scnd->parent);
					instead_scnd = root;
				}
			}
		}
		instead_scnd->isRed = false;
	}

	//replacing first node with second node
	void rbTransplant(NodePtr first_node, NodePtr scnd_node) {
		if (first_node->parent == nullptr) {
			root = scnd_node;
		}
		else if (first_node == first_node->parent->left) {
			first_node->parent->left = scnd_node;
		}
		else {
			first_node->parent->right = scnd_node;
		}
		scnd_node->parent = first_node->parent;
	}

	void deleteNodeHelper(NodePtr node, char key) {
		NodePtr cur = NIL;
		NodePtr instead_scnd, instead_first;
		bool found = false;
		while (node != NIL) {
			if (node->symb == key) {
				cur = node;
				found = true;
			}
			if (node->symb <= key) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}

		if (found == false && node == NIL) {
			throw "There's no key like that";
			return;
		}



		instead_first = cur;
		bool instead_original_color = instead_first->isRed;
		if (cur->left == NIL) {
			instead_scnd = cur->right;
			rbTransplant(cur, cur->right);
		}
		else if (cur->right == NIL) {
			instead_scnd = cur->left;
			rbTransplant(cur, cur->left);
		}
		else {
			instead_first = minimum(cur->right);
			instead_original_color = instead_first->isRed;
			instead_scnd = instead_first->right;
			if (instead_first->parent == cur) {
				instead_scnd->parent = instead_first;
			}
			else {
				rbTransplant(instead_first, instead_first->right);
				instead_first->right = cur->right;
				instead_first->right->parent = instead_first;
			}

			rbTransplant(cur, instead_first);
			instead_first->left = cur->left;
			instead_first->left->parent = instead_first;
			instead_first->isRed = cur->isRed;
		}
		delete cur;
		if (instead_original_color == false) {
			fixDelete(instead_scnd);
		}
	}

	// fix the red-black tree
	void fixInsert(NodePtr key) {
		NodePtr uncle;
		while (key->parent->isRed == true) {
			if (key->parent == key->parent->parent->right) {
				uncle = key->parent->parent->left; // uncle
				if (uncle->isRed == true) {
					// case 3.1 - 
					uncle->isRed = false;
					key->parent->isRed = false;
					key->parent->parent->isRed = true;
					key = key->parent->parent;
				}
				else {
					if (key == key->parent->left) {
						// case 3.2.2 - 
						key = key->parent;
						rightRotate(key);
					}
					// case 3.2.1 - 
					key->parent->isRed = false;
					key->parent->parent->isRed = true;
					leftRotate(key->parent->parent);
				}
			}
			else {
				uncle = key->parent->parent->right;

				if (uncle->isRed == true) {
					// mirror case 3.1 - 
					uncle->isRed = false;
					key->parent->isRed = false;
					key->parent->parent->isRed = true;
					key = key->parent->parent;
				}
				else {
					if (key == key->parent->right) {
						// mirror case 3.2.2 - 
						key = key->parent;
						leftRotate(key);
					}
					// mirror case 3.2.1
					key->parent->isRed = false;
					key->parent->parent->isRed = true;
					rightRotate(key->parent->parent);
				}
			}
			if (key == root) {
				break;
			}
		}
		root->isRed = false;
	}

	void printHelper(NodePtr root, string indent, bool last) {
		// print the tree structure on the screen
		if (root != NIL) {
			cout << indent;
			if (last) {
				cout << "Right-";
				indent += "     ";
			}
			else {
				cout << "Left--";
				indent += "|    ";
			}

			string sColor = root->isRed ? "RED" : "BLACK";
			if (root->symb == ' ')
				cout << "_";
			else
				cout << root->symb;
			cout << " " << root->value << "(" << sColor << ")" << endl;
			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
	}

public:
	shannonfano() {
		NIL = new Node;
		NIL->isRed = false;
		NIL->left = nullptr;
		NIL->right = nullptr;
		root = NIL;
	}

	void preorder() {
		preOrderHelper(this->root);
	}

	void inorder(bool keys, bool values) {
		inOrderHelper(this->root, keys, values);
	}

	void postorder() {
		postOrderHelper(this->root);
	}

	NodePtr find(char k) {
		return searchTreeHelper(this->root, k);
	}

	// find the node with the minimum key
	NodePtr minimum(NodePtr node) {
		while (node->left != NIL) {
			node = node->left;
		}
		return node;
	}

	// find the node with the maximum key
	NodePtr maximum(NodePtr node) {
		while (node->right != NIL) {
			node = node->right;
		}
		return node;
	}

	// find the successor of a given node
	NodePtr successor(NodePtr x) {
		if (x->right != NIL) {
			return minimum(x->right);
		}

		NodePtr y = x->parent;
		while (y != NIL && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	// find the predecessor of a given node
	NodePtr predecessor(NodePtr x) {
		if (x->left != NIL) {
			return maximum(x->left);
		}

		NodePtr y = x->parent;
		while (y != NIL && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}

	void leftRotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != NIL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != NIL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	// insert the key to the tree in its appropriate position
	// and fix the tree
	void insert(char key) {
		NodePtr node = new Node;
		node->parent = nullptr;
		node->symb = key;
		node->value = 1;
		node->left = NIL;
		node->right = NIL;
		node->isRed = true;

		NodePtr items_parent = nullptr;
		NodePtr item = this->root;

		while (item != NIL) {
			items_parent = item;

			if (node->symb < item->symb) {
				item = item->left;
			}
			else if (node->symb == item->symb) {
				item->value++;
				return;
			}
			else {
				item = item->right;
			}
		}

		node->parent = items_parent;
		if (items_parent == nullptr) {
			root = node;
		}
		else if (node->symb < items_parent->symb) {
			items_parent->left = node;
		}
		else {
			items_parent->right = node;
		}

		// if new node is a root node, simply return
		if (node->parent == nullptr) {
			node->isRed = false;
			return;
		}

		// if the grandparent is null, simply return
		if (node->parent->parent == nullptr) {
			return;
		}

		// Fix the tree
		fixInsert(node);
	}

	NodePtr getRoot() {
		return this->root;
	}

	void remove(char data) {
		deleteNodeHelper(this->root, data);
	}

	void Print() {
		if (root != NIL) {
			printHelper(this->root, "", true);
		}
		else {
			try {
				if (root == NIL)
					throw "The tree is empty";
			}
			catch (const char* msg)
			{
				cout << msg << endl;
			}
		}

	}

	void clear()
	{
		if (root != NIL) {
			clearHelper(this->root);
			this->root = NIL;
		}
		else
		{
			try {
				if (root == NIL)
					throw "The tree is empty";
			}
			catch (const char* msg)
			{
				cout << msg << endl;

			}
		}

	}

	void clearHelper(NodePtr root)
	{
		if (root != NIL)
		{
			clearHelper(root->left);
			clearHelper(root->right);
			delete root;
		}


	}

	void show_codes() {
		inorder(true, false);
	}

	void get_values() {
		inorder(false, true);
	}

	//to make a sorted list of chars by freq
	void makinglistHelper(NodePtr node)
	{
		if (node != NIL) {
			sorted.insert_sorted(node->value, node->symb);
			makinglistHelper(node->left);
			makinglistHelper(node->right);
		}
	}

	void plus(List_node* listnode, bool zero)
	{
		NodePtr cur;
		cur = find(listnode->symb);

		if (zero == true) {

			listnode->code += "0";
			cur->code.enqueue(false);
		}

		else {
			listnode->code += "1";
			cur->code.enqueue(true);
		}

	}

	void show_as_list() {
		sorted.print_to_console();
	}

	//Shannon-Fano algorithm
	void encoding_helper(int index1, int index2) {
		int sum = 0;
		List_node* cur = sorted.get_head();

		for (int i = 0; i < index1; i++)
			cur = cur->Next;


		if (index1 == index2)
			return;


		//if there are two elements going one-by-one, one goes to left, one - to the right
		else if (index2 - index1 == 1 && sorted.get_pointer(index1)->washere == false && sorted.get_pointer(index2)->washere == false) { //idut podryad
			plus(sorted.get_pointer(index1), true);
			plus(sorted.get_pointer(index2), false);
			sorted.get_pointer(index1)->washere = true;
			sorted.get_pointer(index2)->washere = true;

		}

		else {
			for (int i = index1; i <= index2; i++) {
				sum += cur->data;
				cur = cur->Next;
			}

			int semisum = sum / 2;
			int isp = -1;
			int cursum = 0;

			//if there are more than two element, they have to be diveded by sum
			for (int i = index1; i <= index2; i++)
			{
				cursum += sorted.get_pointer(i)->data;

				if (cursum <= semisum)
					if (sorted.get_pointer(i)->washere == false)
						plus(sorted.get_pointer(i), true);
				if (cursum > semisum) {
					if (isp < 0) isp = i;
					if (sorted.get_pointer(i)->washere == false)
						plus(sorted.get_pointer(i), false);
				}

			}

			if (isp < 0) isp = index2 - 1;
			encoding_helper(index1, isp - 1);
			encoding_helper(isp, index2);
		}
	}

	//encoding the message
	void encoding_tree() {

		if (root != NIL) {

			makinglistHelper(this->root);

			//encoding in that sorted list of freq
			encoding_helper(0, sorted.get_size() - 1);
		}

		else {
			try {
				if (root == NIL)
					throw "The tree is empty";
			}
			catch (const char* msg)
			{
				cout << msg << endl;

			}
		}

	}

	void show_encoded(string quote) {
		NodePtr node;
		for (int i = 0; i < quote.length(); i++) {
			node = find(quote[i]);
			node->code.show_queue();
		}
	}

	//comparing coming codes with codes in the map
	void compare_codes(string part, NodePtr node, bool& found, string& decoded) {
		if (node != NIL) {
			if (found == true)
				return;
			compare_codes(part, node->left, found, decoded);
			compare_codes(part, node->right, found, decoded);
			if (node->code.compare(part, found) == true) {
				found = true;
				decoded += node->symb;
				return;
			}

		}
	}

	//decoding the message
	void decoding(string line, string& decoded) {
		string part;

		for (int i = 0; i < line.length(); i++) {
			part += line[i];
			bool found = false;
			compare_codes(part, root, found, decoded);
			//if we found the same code, means that another character starts
			if (found == true) {
				part.clear();
			}

		}

	}
}; 
