#include <iostream>
#include <map>
#include <vector>


using namespace std;

struct node {
	long long key;
	long long value;
	node *left, *right;
};

node *newNode(node *&temp, long long key, long long value, long long l_key, long long r_key) {

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


bool IsBinary(node *root, long long& _max, long long& _min, int& first_t) {

	if (first_t == 0) {
		_min = root->value;
		_max = root->value;
		++first_t;
	}
	else {
		if (root->left != NULL) {
			if (root->value <= root->left->value || _max >= root->value
					|| root->value <= _min){
				return false;
			}
			else {
				_min = root->left->value;
				_max = root->value;
			}
		}
		else {
			if (root->value < _min) {
				return false;
			}
			_min = root->value;
			_max = root->value;
		}

		if (root->right != NULL) {
			if (root->value > root->right->value){
				return false;
			}
			else {
				if (root->value < _min) {
					_min = root->value;
				}
				_max = root->right->value;
			}
		}
	}
	return true;
}

void in_order(node *root, vector<bool>& b_vector, long long& _max, long long& _min, int&  first_t) {
  if (root != NULL) {
    in_order(root->left, b_vector, _max, _min, first_t);

    b_vector.push_back(IsBinary(root, _max, _min, first_t));
    //cout << root->value << " ";
    in_order(root->right, b_vector, _max, _min, first_t);
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

	long long _min = 0, _max = 0;

	long long n = 0, left = 0, right = 0, value = 0;
	std::cin >> n;

	map<long long, node*> nodes;
	node *root = new node;
	for (long long key = 0; key < n; ++key) {
		std::cin >> value >> left >> right;
		root = NULL;
		nodes[key] = newNode(root, key, value, left, right);
	}


	for (long long i = 0; i < n; ++i) {
		if (nodes[i]->left != NULL) {
			long long l_key = nodes[i]->left->key;
			Insert(nodes[i]->left, nodes[l_key]);
		}
		if (nodes[i]->right != NULL) {
			long long r_key = nodes[i]->right->key;
			Insert(nodes[i]->right, nodes[r_key]);
		}

	}


	vector<bool> b_vector; // if at least one element == false - incorrect
	int right_bypass = 0, first_t = 0;
	in_order(nodes[0], b_vector, _max, _min,  first_t);
	int ans = 1;
	for (bool e : b_vector) {
		if (e == false) {
			ans = 0;
			break;
		}
	}
	if(ans){
		cout << "CORRECT";
	}
	else {
		cout << "INCORRECT";
	}
}
