#include "stdafx.h"
#include <iostream>

#include <queue>
#include <vector>
#include <string>
#include <utility>

using std::queue;
using std::string;
using std::vector;
using std::pair;

struct node
{
	int n; // value of node
	struct node *left; // left subtree
	struct node *right; // right subtree
	struct node *level; // level pointer (node “to the right”)
};

void linkSameLevel(struct node* t)
{
	queue<node*> leafs;
	leafs.push(t);

	// null marker to represent end of current level
	leafs.push(nullptr);

	while (!leafs.empty()) {

		node *frontNode = leafs.front();
		leafs.pop();

		if (frontNode != nullptr) {

			// next element in queue is the same that
			// next nade at current level
			frontNode->level = leafs.front();

			if (frontNode->left) { leafs.push(frontNode->left); }
			if (frontNode->right) { leafs.push(frontNode->right); }

		}

		// if queue is not empty, push nullptr to mark 
		// nodes at this level are visited
		else {

			if (!leafs.empty()) { leafs.push(nullptr); }

		}
	}
}

node* newNode(int key)
{
	node* node = new struct node;
	node->n = key;
	node->left = nullptr;
	node->right = nullptr;
	return node;
}

// Function to insert given key into the tree
void insert(node*& root, string level, int key)
{
	// tree is empty
	if (level == "ROOT") {

		root = newNode(key);
		return;

	}

	int i = 0;
	node* tempNode = root;

	while (i < level.length() - 1) {

		if (level[i++] == 'L') { tempNode = tempNode->left; }
		else { tempNode = tempNode->right; }
			
	}

	if (level[i] == 'L') { 
		tempNode->left = newNode(key); 
	}
	else { 
		tempNode->right = newNode(key); 
	}

}


int main()
{

	node* root = nullptr;
	vector<pair<string, int>> keys = {
		{ "ROOT", 1 }, { "L", 2 }, { "R", 3 }, { "LL", 4 }, { "LR", 5 },
		{ "RR", 6 }, { "RRL", 7 }, { "RRR", 8 }
	};

	for (auto pair : keys) {
		insert(root, pair.first, pair.second);
	}

	linkSameLevel(root);

	// Let us check the values of level pointers
	printf("Following are populated level pointers in \n"
		"the tree (-1 is printed if there is no level) \n");
	printf("level of %d is %d \n", root->n,
		root->level ? root->level->n : -1);
	printf("level of %d is %d \n", root->left->n,
		root->left->level ? root->left->level->n : -1);
	printf("level of %d is %d \n", root->right->n,
		root->right->level ? root->right->level->n : -1);
	printf("level of %d is %d \n", root->left->left->n,
		root->left->left->level ? root->left->left->level->n : -1);

	printf("level of %d is %d \n", root->left->right->n,
		root->left->right->level ? root->left->right->level->n : -1);

	printf("level of %d is %d \n", root->right->right->n,
		root->right->right->level ? root->right->right->level->n : -1);

	printf("level of %d is %d \n", root->right->right->left->n,
		root->right->right->left->level ? root->right->right->left->level->n : -1);
	printf("level of %d is %d \n", root->right->right->right->n,
		root->right->right->right->level ? root->right->right->right->level->n : -1);

	getchar();
	return 0;
}