/*
 * test_BinTree.cpp
 *
 *  Created on: 27 áðåá× 2016
 *      Author: Liron
 */

#include "Department.h"



int main(){
	Department* d= new Department();
	d->addMagizoologist(55);
	d->addMagizoologist(32);

	d->addCreature(5,55,8);
	d->addCreature(5,55,9);

}
