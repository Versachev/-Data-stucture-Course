#include <iostream>
#include <string>
#include <map>


using namespace std;

struct node {
  int key;
  int value;
  node *left, *right;
};

node *newNode(node *&temp, int key, int value, int l_key, int r_key) {

  temp = new node;
  temp->left = new node;
  temp->right = new node;
  temp->key = key;
  temp->value = value;
  if (l_key == -1) {
	temp->left = NULL;
  }
  else {
	  temp->left->key = l_key;
	  temp->left->left = temp->left->right = NULL;
  }
  if (r_key == -1) {
	temp->right = NULL;
  }
  else {
	 temp->right->key = r_key;
	 temp->right->left = temp->right->right = NULL;
  }
  return temp;

}


void inorder(node *root) {
  if (root != NULL) {
    inorder(root->left);
    cout << root->value << " ";
    inorder(root->right);
  }
}


void pre_order(node *root) {
	if (root == NULL) {
	   return;
	}
	cout << root->value << " ";
	pre_order(root->left);
	pre_order(root->right);

}


void post_order(node *root) {
	if (root == NULL) {
	   return;
	}
	post_order(root->left);
	post_order(root->right);
    cout << root->value << " ";

}


void Insert(node *&p_node, node *&c_node) {

  p_node->left = c_node->left;
  p_node->right = c_node->right;
  p_node->value = c_node->value;
}


int main() {
	int n = 5, left = 0, right = 0, value = 0;
	std::cin >> n;

	map<int, node*> nodes;
	node *root = new node;
	for (int key = 0; key < n; ++key) {
		std::cin >> value >> left >> right;
		root = NULL;
		nodes[key] = newNode(root, key, value, left, right);
	}


	for (int i = 0; i < n; ++i) {
		if (nodes[i]->left != NULL) {
			int l_key = nodes[i]->left->key;
			Insert(nodes[i]->left, nodes[l_key]);
		}
		if (nodes[i]->right != NULL) {
			int r_key = nodes[i]->right->key;
			Insert(nodes[i]->right, nodes[r_key]);
		}

	}
	root = nodes[0];
	inorder(nodes[0]);
	cout << endl;
	pre_order(nodes[0]);
	cout << endl;
	post_order(nodes[0]);
}
