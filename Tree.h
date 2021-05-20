#pragma once
#include "Queue.h"

class Tree {
public:
	node* root;
private:

	void destroySubTree(node* nodee) {			// Used to destroy a subtree

		if (nodee != NULL) {
			destroySubTree(nodee->left);
			destroySubTree(nodee->right);

			delete nodee;

			nodee = NULL;
		}
	}

	void inOrder(node* root) {				// Displaying binary tree
		if (root != NULL) {
			inOrder(root->left);
			cout << "|     " << root->data << "    |     " << root->freq << "\t|" << endl;
			cout << " ----------------------- " << endl;
			inOrder(root->right);
		}
	}

	void encodingTree(node* root, string str, int n, char charArray[], string stringArray[])  	// Recursively finds the bit strings for every symbol in the tree
	{
		if (root == nullptr)
			return;

		// found a leaf node
		if (!root->left && !root->right) {

			int index=0;
			for (int i = 0; i < n; i++) {
				if (charArray[i] == root->data) {
					index = i;
					break;
				}
			}

			stringArray[index] = str;
		}

		encodingTree(root->left, str + "0", n, charArray, stringArray);
		encodingTree(root->right, str + "1", n, charArray, stringArray);
	}

	void copyTreeToSelf(node*& copiedTreeRoot, node* otherTreeRoot)  		// Copying second tree to the first
	{
		if (otherTreeRoot == NULL)
			copiedTreeRoot = NULL;

		else
		{
			copiedTreeRoot = new node;
			copiedTreeRoot->data = otherTreeRoot->data;
			copiedTreeRoot->freq = otherTreeRoot->freq;

			copyTreeToSelf(copiedTreeRoot->left, otherTreeRoot->left);
			copyTreeToSelf(copiedTreeRoot->right, otherTreeRoot->right);
		}
	}

public:

	Tree() {
		root = NULL;
	}

	~Tree()
	{
		this->destroySubTree(root);
	}

	void displayPostOrder()
	{
		cout << " ----------------------- " << endl;
		cout << "   Node    |    Freq " << endl;
		cout << " ----------------------- " << endl;
		this->inOrder(root);
	}

	void copyTree(node* otherTreeRoot)
	{
		this->copyTreeToSelf(root, otherTreeRoot);
	}

	void encode(int n, char charArray[], string stringArray[])
	{
		string str;
		this->encodingTree(root, str, n, charArray, stringArray);
	}
};