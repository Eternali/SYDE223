#include <iostream>
#include "lab4_binary_search_tree.hpp"
#include <queue>


using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
	size = 0;
	root = NULL;
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
    if (!root) {
        return;
    }

    std::queue<BinarySearchTree::TaskItem*> node_queue;
    node_queue.push(root);
    while (!node_queue.empty()) {
        BinarySearchTree::TaskItem* cur_node = node_queue.front();
        node_queue.pop();
        if (cur_node->left) {
            node_queue.push(cur_node->left);
        }
        if (cur_node->right) {
            node_queue.push(cur_node->right);
        }
        delete cur_node;
    }
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
	if (!root) {
		return 0;
	}
	unsigned int total_num = 0;

	std::queue<BinarySearchTree::TaskItem*> node_queue;
	node_queue.push(root);
	while (!node_queue.empty()) {
		BinarySearchTree::TaskItem* cur_node = node_queue.front();
		node_queue.pop();
		total_num ++;
		if (cur_node->left) {
			node_queue.push(cur_node->left);
		}
		if (cur_node->right) {
			node_queue.push(cur_node->right);
		}
	}
	return total_num;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
	if(!root) {
		return BinarySearchTree::TaskItem(-1, "N/A");
	}
	BinarySearchTree::TaskItem* cur_node = root;
	while (cur_node->right) {
		cur_node = cur_node -> right;
	}
	return BinarySearchTree::TaskItem(cur_node->priority, cur_node->description);
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const {
	if(!root) {
		return BinarySearchTree::TaskItem(-1, "N/A");
	}
	BinarySearchTree::TaskItem* cur_node = root;

	while (cur_node->left) {
        cur_node = cur_node -> left;
	}
	return BinarySearchTree::TaskItem(cur_node->priority, cur_node->description);
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {

	BinarySearchTree::TaskItem* cur_node = root;
	if (!cur_node){ // if completely empty
		return 0;
	}
	queue<BinarySearchTree::TaskItem* > q;

	q.push(cur_node);
	unsigned int height = 0; // start at 0

	while(true) {
		int nodeCount = q.size();
		if (nodeCount == 0){
			if(height == 0) return 0; // will be 0 indexed for top row... so if completely empty or 1 item still 0
			return height -1;
		}
		height++;

		while(nodeCount > 0) { // remove all items from previous row and add all items in next row
			BinarySearchTree::TaskItem* node = q.front();
			q.pop();
			if (node->left)
				q.push(node->left);
			if (node->right)
				q.push(node->right);
			nodeCount--;
		}
	}
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
	if (!root) {
		return;
	}

	std::queue<BinarySearchTree::TaskItem*> node_queue;
	node_queue.push(root);
	while (!node_queue.empty()) {
		BinarySearchTree::TaskItem* cur_node = node_queue.front();
		node_queue.pop();
		if (cur_node->left) {
			node_queue.push(cur_node->left);
		}
		if (cur_node->right) {
			node_queue.push(cur_node->right);
		}
	}
}

// PURPOSE: Returns true if a node with the value val exists in the tree	
// otherwise, returns false
bool BinarySearchTree::exists( BinarySearchTree::TaskItem val ) const {
	if(!root) {
		return false;
	}
	BinarySearchTree::TaskItem* cur_node = root;

	while(cur_node) {
		if(val.priority > cur_node->priority){
			if(cur_node->right){
				cur_node = cur_node -> right;
			} else {
				return false;
			}
		} else if(val.priority < cur_node->priority){
			if(cur_node->left){
				cur_node = cur_node -> left;
			} else{
				return false;
			}
		} else {
			return true;
		}
	}
	return false;
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
    return root;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
    return &root;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
	return 0;
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {

	if(!root) {
		root =  new BinarySearchTree::TaskItem(val.priority, val.description);
		size ++;
		return true;
	}

	BinarySearchTree::TaskItem* cur_node = root;

	while(cur_node) {

		if(val.priority > cur_node->priority){
			if(cur_node->right){
				cur_node = cur_node -> right;
			} else {
				cur_node -> right =  new BinarySearchTree::TaskItem(val.priority, val.description);
				size ++;
				return true;
			}
		} else if(val.priority < cur_node->priority){
			if(cur_node->left){
				cur_node = cur_node -> left;
			} else{
				cur_node -> left =  new BinarySearchTree::TaskItem(val.priority, val.description);
				size ++;
				return true;
			}
		} else {
			return false;
		}
	}
	return false;
}


BinarySearchTree::TaskItem* BinarySearchTree::minValueNode( BinarySearchTree::TaskItem* node) {
	BinarySearchTree::TaskItem* current = node;

	// loop down to find the leftmost leaf
	while (current->left != NULL)
		current = current->left;
	return current;
}


BinarySearchTree::TaskItem* BinarySearchTree::deleteNode( BinarySearchTree::TaskItem* root, int priority, bool *is_success) {
	if (!root) return root;

	if (priority < root->priority)
		root->left = BinarySearchTree::deleteNode(root->left, priority, is_success);

	else if (priority > root->priority)
		root->right = BinarySearchTree::deleteNode(root->right, priority, is_success);

	else {
		// no children
		if(!(root->left)&&!(root->right)){
			delete root;
			*is_success = true;
			return NULL;
		} else if (!(root->left)) { // one child
			BinarySearchTree::TaskItem* temp = new BinarySearchTree::TaskItem(-1, "");
			temp = root->right;
			delete root;
			*is_success = true;
			return temp;
		}
		else if (!(root->right)) {
			BinarySearchTree::TaskItem* temp = new BinarySearchTree::TaskItem(-1,"");
			temp = root->left;
			delete root;
			*is_success = true;
			return temp;
		}

		// node with two children: Get the inorder successor (smallest in the right subtree)
		BinarySearchTree::TaskItem* temp = BinarySearchTree::minValueNode(root->right);

		root->priority = temp->priority;
		root->description = temp ->description;

		// Delete the inorder successor
		root->right = BinarySearchTree::deleteNode(root->right, temp->priority, is_success);
	}
	return root;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove( BinarySearchTree::TaskItem val ) {
	bool *is_success = new bool;
	*is_success = false; // flag that recursive function can change bc dynamic

	root = deleteNode(root, val.priority, is_success);

	if(*is_success){
		delete is_success; // delete dynamic memory
		return true;
	}
	delete is_success; // delete dynamic memory
	return false;
}
