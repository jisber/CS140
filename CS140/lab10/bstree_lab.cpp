//Jacob Isber
//Lab 10 
//In this lab I was helped by, Thomas(TA), and Chaohui Zheng(TA).
//Rev 1.0
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include "bstree.hpp"
using namespace std;
using CS140::BSTree;
using CS140::BSTNode;

/* ---------------------------------------------- */
/* You'll write all of these as part of your lab. */

//Finds the depth of the tree.
int BSTree::Depth(const string &key) const
{
	BSTNode *n;	
	int counter = 0;
	n = sentinel->right;
	while(1) {
		if(key == n->key) {
			return counter;
		}		
		 if(key < n->key) {
			counter++;
			n =	n->left;
		}
		else if(key > n->key) {
			counter++;
			n = n->right;
		}
		if(n == sentinel) {
			break;
		}

	}

  return -1;
}

//Finds the height of the tree by calling a recurrsive function
int BSTree::Height() const
{
	BSTNode *n;
	n = sentinel->right;

	return recursive_find_height(n);
}

vector <string> BSTree::Ordered_Keys() const
{
  vector <string> rv;
  BSTNode *n;
  

  n = sentinel->right;
  make_key_vector(n, rv);
  return rv;
}

//This is the copy constructor, this uses the assignment overload as well as setting the sentinel node.
BSTree::BSTree(const BSTree &t)        
{
	sentinel = new BSTNode;
	sentinel->left = NULL;
	sentinel->right = sentinel;
	sentinel->parent = NULL;
	sentinel->key = "---SENTINEL---";
	sentinel->val = NULL;
	size = 0;

  vector <string> key;
  vector <void *> val;

  BSTNode *n;

  Clear();

  key = t.Ordered_Keys();
  val = t.Ordered_Vals();
	
  n = make_balanced_tree(key, val, 0, key.size());

  sentinel->right = n;
	
  size = key.size();

}

//This is the assignment overload
BSTree& BSTree::operator= (const BSTree &t) 
{
  vector <string> key;
  vector <void *> val;

  BSTNode *n;

  Clear();

  key = t.Ordered_Keys();
  val = t.Ordered_Vals();
	
  n = make_balanced_tree(key, val, 0, key.size());

  sentinel->right = n;
	
  size = key.size();

  return *this;
}

//This is finding the height reccursivly 
int BSTree::recursive_find_height(const BSTNode *n) const
{ 
	int Depth1, Depth2;

	if(n == sentinel) {
		return 0;
	}
	Depth1 = recursive_find_height(n->left);
	Depth2 = recursive_find_height(n->right);
	
	if(Depth1 > Depth2)
		return (Depth1 + 1);
	else 
		return (Depth2 + 1);
}
//Stores the keys in the vector
void BSTree::make_key_vector(const BSTNode *n, vector<string> &v) const
{	
	if(n == sentinel) return;
	make_key_vector(n->left, v);
	v.push_back(n->key);
	make_key_vector(n->right, v);
}

//This is the make balanced tree, it is used inside the assignment overload.
BSTNode *BSTree::make_balanced_tree(const vector<string> &sorted_keys, const vector<void *> &vals,
                            size_t first_index,
                            size_t num_indices) const
{

	if(num_indices == 0){
		return sentinel;
	}
	
	BSTNode *n = new BSTNode;
	
	int num  = (num_indices) / 2;
	n->left = make_balanced_tree(sorted_keys, vals, first_index, num);
	n->right = make_balanced_tree(sorted_keys, vals, first_index + num + 1, (num_indices - 1) / 2);

	n->key = sorted_keys[first_index + num];
	n->val = vals[first_index + num];
	
	n->left->parent = n;
	n->right->parent = n;

  return n;
}
		
	
