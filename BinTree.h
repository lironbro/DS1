/*
 * AVLTree.h
 *
 *  Created on: 4 בדצמ 2016
 *      Author: user
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <exception>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>


template <class T>


class AVLTree
{


private:

	T* info;
	int index;
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
			lSize = right->size;
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
	void aux_fillFromArray(int* indexes, T** info, int i){
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
	void aux_turnToArrays(int* indexes ,T** info, int i){
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
	AVLTree (T* info=NULL,int index=-1):
		info(info),index(index) ,parent(NULL), left(NULL), right(NULL), size(0) , height(0)
	{

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
	AVLTree* findParent(int index){
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
	T* find(int index){
		if(this == NULL){
			return NULL;
		}
		else if(this->index == index){
			return this->info;
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
	 */
	void insert(T* info ,int index) {
		if (this->parent == NULL && this->size == 0){
			this->info = info;
			this->index = index;
			this->size = 1;
			this->height = 1;
			return;
		}
		if (this ->index == index){
			throw new AlreadyExistsException();
		}
		else if(this->index > index){
			if(this->left == NULL ){
				this->left = new AVLTree(info,index);
				this->left->parent = this;
			}
			else{
				this->left->insert(info,index);
			}
		}
		else{
			if(this->right == NULL){
				this->right = new AVLTree(info,index);
				this->right->parent = this;
			}
			else{
				this->right->insert(info,index);
			}
		}

		updateSize();
		updateHeight();
	}


	/*
	 * removes the node from the tree with the given index
	 */
	void remove(int index){
		if(this == NULL){
			throw new NotFoundException();
		}
		else if(this->index == index){
			if(this->left == NULL && this->right == NULL){
				if(this->parent == NULL){

				}
			}
		}
	}


	/*
	 * returns a pointer to an avl tree which will be the almost full tree
	 * which will consist of index-info nodes as in the given arrays
	 */
	static AVLTree<T>* fillFromArray(int* indexes, T** info, int n)
			{
		AVLTree<T>* res = new AVLTree<T>(n);			// TODO: fuck this stupid fucking language
		res->aux_fillFromArray(indexes, info, 0);
		return res;
			}


	/*
	 * turns the avl tree into a pair of index and info arrays
	 */
	void turnToArrays(int* indexes ,T** info)
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


	int getBalanceFactor()
	{
		return this->left->height - this->right->height;
	}

	void fixBalanceFactor(){
		AVLTree root = this->findBadBalanceFactor();
		if(root == NULL) return;

		if(this->index > root->index){
			if(root->right->getBalanceFactor()==1)
				this->rotatedRL();
			else
				this->rotatedRR()
		}
		else{
			if(root->right->getBalanceFactor()==1)
				this->rotatedRL();
			else
				this->rotatedRR()
		}
	}
}

AVLTree* findBadBalanceFactor(){

	if(this->getBalanceFactor()==2 || this->getBalanceFactor()==-2)
		return this;
	if(this->parent == NULL)
		return NULL;
	return this->parent->findBadBalanceFactor();
}

void rotatedLL(){

}
void rotatedLR(){

}
void rotatedRL(){

}
void rotatedRR(){

}

};


#endif /* AVLTREE_H_ */
