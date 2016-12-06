/*
 * AVLTree.h
 *
 *  Created on: 4 áãöî 2016
 *      Author: user
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <exception>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>


template <class T,class S>

class AVLTree
{

private:
	T* info;
	S index;
	AVLTree* parent;
	AVLTree* left;
	AVLTree* right;
	int size;
	int height;


	/*
	 * updates the size of tree
	 */
	void updateSize(){
		if(this == NULL){
			return;
		}

		int lSize = 0 ,rSize =0;

		if(left != NULL){
			lSize = left->size;
		}
		if(right != NULL){
			rSize = right->size;
		}
		this->size = 1+ rSize +lSize;
		parent->updateSize();
	}


	/*
	 * updates the height of the tree
	 */
	void updateHeight(){
		if(this == NULL){
			return;
		}
		int rHeight, lHeight;
		if(this->right == NULL){
			rHeight = -1;
		}
		else{
			rHeight = this->right->height;
		}
		if(this->left == NULL){
			lHeight = -1;
		}
		else{
			lHeight = this->left->height;
		}

		this->height = rHeight > lHeight ? rHeight + 1 :lHeight + 1;
		this->parent->updateHeight();
	}


	/*
	 * helps with filling an avl tree with values in the index-info arrays
	 */
	void aux_fillFromArray(S* indexes, T** info, int i){
		if(this->left != NULL){
			left->aux_fillFromArray(indexes, info, i);
			i += left->size;
		}
		this->index=indexes[i];
		if(info != NULL){	// in our tests info will be NULL
			this->info = info[i];
		}
		i++;
		if(this->right != NULL)
		{
			right->aux_fillFromArray(indexes, info, i);
		}
	}


	/*
	 * helps with turning the avl tree into an index and info array
	 */
	void aux_turnToArrays(S* indexes ,T** info, int i){
		if (this == NULL){
			return;
		}
		if(left != NULL){
			left->aux_turnToArrays(indexes,info,i);
			i += left->size;
		}

		indexes[i] = index;

		if(info != NULL){
			info[i] = this->info;
		}
		if(right != NULL){
			right->aux_turnToArrays(indexes,info,i+1);
		}
	}


public:

	class AVLException : public std::exception {};
	class NotFoundException: public AVLException {};
	class AlreadyExistsException: public AVLException {};
	class NullPointerException: public AVLException {};

	/*
	 * creates an AVL tree
	 */
	AVLTree(T* info=NULL, S index=false, AVLTree* parent=NULL, int size = 1, int height = 0):
		info(info),index(index) ,parent(parent), left(NULL), right(NULL),
		size(size), height(height)
	{
		if(parent == NULL){		// creating an empty tree
			this->size = 0;
			this->height = 0;
		}
	}




	~AVLTree(){
		if(right != NULL) delete right;
		if(left != NULL) delete left;
	}

	/*
	 * creates an almost complete tree, which will have empty info
	 * slots and indexes of 0
	 * the height and size parameters should be correct
	 */
	AVLTree(int n, AVLTree* parent = NULL):
		info(NULL), index(0), parent(NULL), left(NULL), right(NULL), size(n),
		height(0){
		if(n < 1)		// this should never happen
			return ;
		if(n == 1)
		{
			height = 1;
			return;
		}
		this->height = floor(log2(n))+1;
		int fullLeaves = pow(2, height-1);
		int fullTree = pow(2, height)-1;
		int dif = fullTree - n;		// the number of leaves missing for the tree to be full
		if(dif == 0)	// if full tree
		{
			this->left = new AVLTree((fullTree-1)/2, this);
			this->right = new AVLTree((fullTree-1)/2, this);
		}
		else if(dif >= fullLeaves/2)	// if leaves only exist in left subtree
		{
			this->left = new AVLTree(fullTree/2 + fullLeaves/2 - dif, this);
			if(fullTree/2 - fullLeaves/2 > 0)
				this->right = new AVLTree(fullTree/2 - fullLeaves/2, this);
		}
		else{		// if leaves exist in both subtrees
			this->left = new AVLTree(fullTree/2, this);
			if(fullTree/2 - dif > 0)
				this->right = new AVLTree(fullTree/2 - dif, this);
		}
	}


	/*
	 * finds the parent of the node with the requested index
	 */
	AVLTree* findParent(S index){
		if(this == NULL){
			return NULL;
		}
		else if(this->left->index == index || this->right->index == index){
			return this;
		}
		else if(index < this->index){
			return this->left->find(index);
		}
		else{
			return this->right->find(index);
		}
	}


	/*
	 * finds the value of the node with the requested index
	 */
	AVLTree* find(S index){
		if(this == NULL){
			return NULL;
		}
		else if(this->index == index){
			return this;
		}
		else if(index < this->index){
			return this->left->find(index);
		}
		else{
			return this->right->find(index);
		}
	}


	/*
	 * inserts the index and info into the AVL tree
	 * returns the root of the tree
	 */
	AVLTree* insert(T* info ,S index) {
		if (this->parent == NULL && this->size == 0){	// if the tree is empty
			this->info = info;
			this->index = index;
			this->size = 1;
			this->height = 0;
			return this;
		}
		if (this ->index == index){
			throw AlreadyExistsException();
		}
		else if(this->index > index){
			if(this->left == NULL ){
				this->left = new AVLTree(info,index, this);
				updateSize();
				updateHeight();
				fixBalanceFactorInsert();		// should go up to the problematic node
				return getRoot();
			}
			else{
				return this->left->insert(info,index);
			}
		}
		else{
			if(this->right == NULL){
				this->right = new AVLTree(info,index, this);
				updateSize();
				updateHeight();
				fixBalanceFactorInsert();
				return getRoot();
			}
			else{
				return this->right->insert(info,index);
			}
		}
	}


	/*
	 * returns the root of the entire tree
	 */
	AVLTree* getRoot(){
		if(this == NULL)
			return NULL;
		if(this->parent == NULL)
			return this;
		return parent->getRoot();
	}


	/*
	 * removes the node from the tree with the given index
	 */
	AVLTree* remove(S index){
		if(this == NULL){
			throw NotFoundException();
		}
		else if(this->index == index){
			if(this->left == NULL && this->right == NULL){
				if(this->parent != NULL){
					if(this == this->parent->left) this->parent->left = NULL;
					else
						this->parent->right = NULL;

					AVLTree* tmp = this->parent;
					delete this;
					tmp->updateHeight();
					tmp->updateSize();
					AVLTree* y = tmp->fixBalanceFactorRemove();
					return y;
				}
				else{
					delete this->info;
					this->size = 0;
					this->height = -1;
					return this;
				}
			}
			else if(this->left == NULL && this->right != NULL){
				if(this->parent != NULL){
					if(this == this->parent->left) this->parent->left = this->right;
					else this->parent->right = this->right;

					this->right->parent = this->parent;
					AVLTree* tmp = this->parent;
					delete this;
					tmp->updateHeight();
					tmp->updateSize();
					return tmp->fixBalanceFactorRemove();
				}
				else{
					AVLTree* tmp = this->right;
					delete this;
					return tmp;
				}
			}
			else if(this->left != NULL && this->right == NULL){
				if(this->parent != NULL){
					if(this == this->parent->left) this->parent->left = this->left;
					else
						this->parent->right = this->left;

					this->left->parent = this->parent;
					AVLTree* tmp = this->parent;
					delete this;
					tmp->updateHeight();
					tmp->updateSize();
					return tmp->fixBalanceFactorRemove();
				}
				else{
					AVLTree* tmp = this->left;
					delete this;
					return tmp;
				}
			}
			else if(this->left != NULL && this->right != NULL){
				//if(this->parent != NULL){
				AVLTree* next = this->findNextInorder();

				if(this->right != next){
					AVLTree* tmp = next->right;
					if (this->right != NULL) this->right->parent = next;
					if (next->right != NULL) next->right->parent = this;
					next->right = this->right;
					this->right = tmp;

					tmp = next->left;
					if (this->left != NULL) this->left->parent = next;
					if (next->left != NULL) next->left->parent = this;
					next->left = this->left;
					this->left = tmp;

					tmp = next->parent;
					next->parent = this->parent;
					this->parent = tmp;
				}
				else{
					this->right = next->right;
					next->right = this;

					AVLTree* tmp = next->left;
					next->left = this->left;
					this->left = tmp;

					next->parent = this->parent;
					if(this->parent->right == this){
						this->parent->right = next;
					}else{
						this->parent->left = next;
					}
					this->parent = next;

					next->left->parent = next;
				}
				AVLTree* x =  this->remove(index); //TODO: delete x
				return x;
			}
		}

		else if(index < this->index){
			if(this->left == NULL)
				throw NotFoundException();
			return this->left->remove(index);
		}
		else{
			if(this->right == NULL)
				throw NotFoundException();
			return this->right->remove(index);

		}
		return NULL;
	}



	/*
	 * finds the next element inorder
	 */
	AVLTree* findNextInorder()
	{
		if(this == NULL || this->right == NULL)
			return NULL;
		return this->right->furthestLeft();
	}


	/*
	 * goes left till it hits null, returns one value before that
	 */
	AVLTree* furthestLeft()
	{
		if(this == NULL)
			return NULL;
		if(this->left == NULL)
			return this;
		return this->left->furthestLeft();
	}


	/*
	 * find the node which has a bad balance factor
	 */
	AVLTree* findBadBalanceFactor(){
		int bf = getBalanceFactor();
		if(bf >= 2 || bf <= -2)
			return this;
		if(this->parent == NULL)
			return NULL;
		return this->parent->findBadBalanceFactor();
	}


	/*
	 * fix the node with bad balance factor, return the node that switched places with the old one
	 */
	AVLTree* fixBalanceFactorInsert(){
		AVLTree* root = this->findBadBalanceFactor();
		if(root == NULL)
			return this;

		if(this->index >= root->index){
			if(root->right->getBalanceFactor()==1){
				this->rotateRL(root);
			}
			else{
				this->rotateRR(root);
			}
		}
		else{
			if(root->left->getBalanceFactor()==-1){
				this->rotateLR(root);
			}
			else{
				this->rotateLL(root);
			}
		}
		return root->parent;		// at the end of every rotation the problematic
		// node will be the offspring of the new root
	}


	AVLTree* fixBalanceFactorRemove(){
		if(this->getBalanceFactor() == -2 && this->right != NULL){
			if( this->right->getBalanceFactor() == 1){
				rotateRL(this);
			}
			else{
				rotateRR(this);
			}
		}
		else if (this->getBalanceFactor() == 2 && this->left != NULL){
			if( this->left->getBalanceFactor() == -1){
				rotateLR(this);
			}
			else{
				rotateLL(this);
			}
		}
		return this->parent;
	}


	/*
	 * rotate LL
	 * this is basically a right rotation around root
	 */
	static void rotateLL(AVLTree* root)
	{
		if(root == NULL || root->left == NULL)
			return;

		AVLTree* left = root->left;
		AVLTree* parent = root->parent;

		int h = root->height;				// height
		int n = root->size;					// number of elements in the tree
		int  nAr = 0, nBr = 0;				// get the size of each subtree
		//if(left->left != NULL)			// being replaced
		//	nAl = left->left->size;
		if(left->right != NULL)
			nAr = left->right->size;
		if(root->right != NULL)
			nBr = root->right->size;

		if(parent != NULL){					// update the parent's son
			if(parent->left == root)
				parent->left = left;
			else
				parent->right = left;
		}
		root->parent = left;
		left->parent = parent;
		root->left = left->right;
		left->right = root;

		root->height = h-2;					// update the size and height
		root->size = nAr + nBr + 1;			// of both affected nodes
		left->size = n;
	}


	/*
	 * rotate RR
	 * this is basically a left rotation around root
	 */
	static void rotateRR(AVLTree* root)
	{
		if(root == NULL || root->right == NULL)
			return;

		AVLTree* right = root->right;
		AVLTree* parent = root->parent;

		int h = root->height;				// height
		int n = root->size;					// number of elements in the tree
		int  nAl = 0, nBl = 0;				// get the size of each subtree
		//if(left->left != NULL)			// being replaced
		//	nAl = left->left->size;
		if(right->left != NULL)
			nAl = right->left->size;
		if(root->left != NULL)
			nBl = root->left->size;

		if(parent != NULL){					// update the parent's son
			if(parent->left == root)
				parent->left = right;
			else
				parent->right = right;
		}
		root->parent = right;
		right->parent = parent;
		root->right = right->left;
		right->left = root;

		root->height = h-2;					// update the size and height
		root->size = nAl + nBl + 1;			// of both affected nodes
		right->size = n;
	}


	/*
	 * rotate right and then rotate left
	 */
	static void rotateRL(AVLTree* root)
	{
		if(root == NULL || root->right == NULL || root->right->left == NULL)
			return;
		AVLTree* right = root->right;
		AVLTree* rl = right->left;
		rotateLL(right);
		rotateRR(root);
		rl->height++;
		right->height++;
		root->updateHeight();
	}


	/*
	 * rotate left and then rotate right
	 * root height decreases by 2
	 * left height decreases by 1
	 * lr height increases by 1
	 */
	static void rotateLR(AVLTree* root)
	{
		if(root == NULL || root->left == NULL || root->left->right == NULL)
			return;
		AVLTree* left = root->left;
		AVLTree* lr = left->right;
		rotateRR(left);		// decreases left height by 2, lr height is the same
		rotateLL(root);		// decreases root height by 2, lr height is the same
		lr->height++;
		left->height++;
		root->updateHeight();
	}


	/*
	 * returns a pointer to an avl tree which will be the almost full tree
	 * which will consist of index-info nodes as in the given arrays
	 */
	static AVLTree<T,S>* fillFromArray(S* indexes, T** info, int n)
																																																																			{
		AVLTree<T,S>* res = new AVLTree<T,S>(n);
		res->aux_fillFromArray(indexes, info, 0);
		return res;
																																																																			}


	/*
	 * turns the avl tree into a pair of index and info arrays
	 */
	void turnToArrays(S* indexes ,T** info)
	{
		aux_turnToArrays(indexes ,info, 0);
	}


	/*
	 * returns the size of the tree
	 */
	int getSize()
	{
		return this->size;
	}


	/*
	 * returns the height of the tree
	 */
	int getHeight()
	{
		return this->height;
	}

	T* getInfo(){
		return this->info;
	}


	AVLTree* getParent(){
		return this->parent;
	}


	/*
	 * returns the balance factor
	 */
	int getBalanceFactor()
	{
		if(this == NULL)
			throw NullPointerException();
		int lHeight = -1, rHeight = -1;
		if(left != NULL)
			lHeight = left->height;
		if(right != NULL)
			rHeight = right->height;
		return lHeight - rHeight;
	}

};

#endif /* AVLTREE_H_ */
