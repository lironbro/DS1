/*
 * test_BinTree.cpp
 *
 *  Created on: 27 бреб„ 2016
 *      Author: Liron
 */

#include "AVLTree.h"

int main(){

	//int meaningful = ceil(log2(7));

	// constructor test 	- passed
	AVLTree<int>* tree = new AVLTree<int>();
	int x = 3;
	int y = 5;
	int z = 100000;

	// insert test	- passed
	tree = tree->insert(NULL, 5);
	tree = tree->insert(&z, 2);
	tree = tree->insert(NULL, 1);		// if you insert 1 there should be LL rotation, if 3 then LR
	tree = tree->insert(&x, 10);
	tree = tree->insert(NULL, 12);
	//tree->insert(NULL, 2);		// won't be inserted
	tree = tree->insert(&y, 3);
	tree = tree->insert(NULL, 7);
	tree = tree->insert(NULL, 9);
	tree = tree->insert(NULL, -1);
	tree = tree->insert(NULL, 0);		// should perform LR on node of index 1
	tree = tree->insert(NULL, 8);		// should perform RL on node of index 7

	int val = -1;
	// turnToArrays test 1	- passed
	int* arr = (int*)malloc(tree->getSize()*sizeof(int));
	tree->turnToArrays(arr, NULL);
	for(int i = 0; i < tree->getSize(); i++)
		val = arr[i];


	// height test	- passed
	int height = tree->getHeight();

	// size test	- passed
	int size = tree->getSize();

	// find test	- passed
	AVLTree<int>* t = tree->find(-17);
	t = tree->find(10);
	t = tree->find(-20);
	t = tree->find(3);
	t = tree->find(2);
	t = tree->find(-20);



	// remove test	- passed
	tree->remove(5);	// root
	tree->remove(0);	// leaf
	tree->remove(8);	// one child
	tree->remove(2);	// two children
	tree->remove(2);
	tree->remove(1);	// extras
	tree->remove(9);

	// turnToArrays test 2	- passed
	int* arr2 = (int*)malloc(sizeof(int)*tree->getSize());
	tree->turnToArrays(arr2, NULL);
	for(int i = 0; i < tree->getSize(); i++)
		val = arr[i];

	// almost full tree constructor test	- passed
	// this should work, if it won't, I'll kill myself
	AVLTree<int>* empty1 = new AVLTree<int>(7);
	AVLTree<int>* empty2 = new AVLTree<int>(5);
	AVLTree<int>* empty3 = new AVLTree<int>(6);
	AVLTree<int>* empty4 = new AVLTree<int>(4);

	// fillFromArray test	- passed
	int indexes[7] = {1, 2, 5, 10, 120, 444, 1000};
	AVLTree<int>* treeArr1 = AVLTree<int>::fillFromArray(indexes, NULL, 7);		// info is NULL, should still work
	AVLTree<int>* treeArr2 = AVLTree<int>::fillFromArray(indexes, NULL, 6);		// info is NULL, should still work


	// delete test
	delete empty2;
	delete empty1;
	delete tree;


	delete arr;

}


