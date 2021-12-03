//Jacob Isber
//Lab 11
//12/04/2019
//rev 1
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include "avltree.hpp"
using namespace std;
using CS140::AVLTree;
using CS140::AVLNode;

//Function prototypes
bool imbalance(const AVLNode *n);

void rotate(AVLNode *n);

void fix_height(AVLNode *n);	

void fix_imbalance(AVLNode *n);

//Assignment Overload
AVLTree& AVLTree::operator= (const AVLTree &t)        
{
  Clear();

  sentinel->right= recursive_postorder_copy(t.sentinel->right);
  sentinel->right->parent = sentinel;

  size = t.size;
  return *this;
}

/* I simply took Insert and Delete from their binary search tree
   implementations.  They aren't correct for AVL trees, but they are
   good starting points.  */

bool AVLTree::Insert(const string &key, void *val)
{
  AVLNode *parent;
  AVLNode *n;

  parent = sentinel;
  n = sentinel->right;

  /* Find where the key should go.  If you find the key, return false. */

  while (n != sentinel) {
    if (n->key == key) return false;
    parent = n;
    n = (key < n->key) ? n->left : n->right;
  }

  /* At this point, parent is the node that will be the parent of the new node.
     Create the new node, and hook it in. */

  n = new AVLNode;
  n->key = key;
  n->val = val;
  n->parent = parent;
  n->height = 1;
  n->left = sentinel;
  n->right = sentinel;  

  AVLNode *p = n;

 /* while(h != sentinel) {
	if(h->parent->height == h->height) {
		h->parent->height++;
	}
	h = h->parent;
  }
*/

  
  /* Use the correct pointer in the parent to point to the new node. */

  if (parent == sentinel) {
    sentinel->right = n;
  } else if (key < parent->key) {
    parent->left = n;
  } else {
    parent->right = n;
  }

  fix_height(n);

  /* Increment the size */

  size++;

//Fixes the imbalance
  p = n->parent;
  while(p != sentinel){
  if(imbalance(p)){
	  fix_imbalance(p);
	}
	p = p->parent;
  }

	
  return true;
}
   
bool AVLTree::Delete(const string &key)
{
  AVLNode *n, *parent, *mlc;
  string tmpkey;
  void *tmpval;


  /* Try to find the key -- if you can't return false. */

  n = sentinel->right;
  while (n != sentinel && key != n->key) {
    n = (key < n->key) ? n->left : n->right;
  }
  if (n == sentinel) return false;

  /* We go through the three cases for deletion, although it's a little
     different from the canonical explanation. */

  parent = n->parent;
  AVLNode *p = parent;

  /* Case 1 - I have no left child.  Replace me with my right child.
     Note that this handles the case of having no children, too. */

  if (n->left == sentinel) {
    if (n == parent->left) {
      parent->left = n->right;
    } else {
      parent->right = n->right;
    }
    if (n->right != sentinel) n->right->parent = parent;
    delete n;
    size--;

  /* Case 2 - I have no right child.  Replace me with my left child. */

  } else if (n->right == sentinel) {
    if (n == parent->left) {
      parent->left = n->left;
    } else {
      parent->right = n->left;
    }
    n->left->parent = parent;
    delete n;
    size--;

  /* If I have two children, then find the node "before" me in the tree.
     That node will have no right child, so I can recursively delete it.
     When I'm done, I'll replace the key and val of n with the key and
     val of the deleted node.  You'll note that the recursive call 
     updates the size, so you don't have to do it here. */

  } else {
    for (mlc = n->left; mlc->right != sentinel; mlc = mlc->right) ;
    tmpkey = mlc->key;
    tmpval = mlc->val;
    Delete(tmpkey);
    n->key = tmpkey;
    n->val = tmpval;

    return true;
  }

//Fixes the imbalance
  p = n->parent;
  while(p != sentinel){
	if (p->right->height > p->left->height) 
		p->height = p->right->height + 1;
	else p->height = p->left->height + 1;

	if(imbalance(p)){
	  fix_imbalance(p);
	}
	p = p->parent;
  }

  return true;
}
               
/* You need to write these two.  You can lift them verbatim from your
   binary search tree lab. */

vector <string> AVLTree::Ordered_Keys() const
{
  vector <string> rv;
  make_key_vector(sentinel->right, rv);
	return rv;
}
    
void AVLTree::make_key_vector(const AVLNode *n, vector<string> &v) const
{
	if(n==sentinel) return;
	make_key_vector(n->left, v);
	v.push_back(n->key);
	make_key_vector(n->right, v);
}
     
size_t AVLTree::Height() const
{
  return sentinel->right->height;
}

/* You need to write this to help you with the assignment overload.
   It makes a copy of the subtree rooted by n.  That subtree is part
   of a different tree -- the copy will be part of the tree that
   is calling the method. */

AVLNode *AVLTree::recursive_postorder_copy(const AVLNode *n) const
{
	if(n->height == 0) return sentinel;

	AVLNode *p;

	p = new AVLNode;

	p->left = recursive_postorder_copy(n->left);
	p->right = recursive_postorder_copy(n->right);

	p->key = n->key;
	p->val = n->val;
	p->left->parent = p;
	p->right->parent = p;
	p->height = n->height;

	return p;
}

//Detects whether there was an imbalance or not
bool imbalance(const AVLNode *n) {
	if(abs((int)(n->left->height - n->right->height)) >= 2) return true;	
	else return false;
}

//Rotates the nodes 
//Geeks for geeks does an amazing job explaining the concept of rotation
void rotate(AVLNode *n) {
	
	AVLNode *y;

	//Rotating right
	if(n->left->height > n->right->height){
		y = n->left;
		y->parent = n->parent;
		n->left = y->right; //N left becomes t3
		n->left->parent = n;
		y->right = n; //y right becomes z
		n->parent = y;

	
	}
	
	//Rotating left
	else {
		y = n->right;
		y->parent = n->parent;
		n->right = y->left; 
		n->right->parent = n;
		y->left = n;
		n->parent = y;


	}
		if(y->parent->left == n) y->parent->left = y;
		else y->parent->right = y;

		fix_height(n);
}

//Fixes the nodes height
void fix_height(AVLNode *n) {	
	if(n->height == 0)
		return;

	n->height = max(n->right->height,n->left->height) + 1; 
	fix_height(n->parent);
}


//Fixes the imbalance between nodes
void fix_imbalance(AVLNode *n) {
	
	if(n->left->height > n->right->height) {
		//We are going to rotate right
		
		//Left-Right zig zag
		if(n->left->left->height < n->left->right->height) {
			rotate(n->left);
		}

		rotate(n);
	}
	else
	{
		if(n->right->left->height > n->right->right->height){
			rotate(n->right);
		}

		rotate(n);
	}
}

