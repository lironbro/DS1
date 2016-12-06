/*
 * Department.c
 *
 *  Created on: 5 áãöî× 2016
 *      Author: Liron
 */
#include "Department.h"

/*
 * TODO s:
 * -have exceptions
 * -change functions to work properly
 * -check that adding a creature gives it pointers to both nodes
 * -take Tal's content and add it
 * -test this ship out
 */

Department::Department() : magis(new AVLTree<Magizoologist, int>()), creatures(new AVLTree<Creature, int>()){

}


void Department::addMagizoologist(int id){
	try{
		magis = magis->insert(new Magizoologist(), id);
	}
	catch(AVLTree<Magizoologist, int>::AlreadyExistsException&){
		throw new MagiIDAlreadyExistsException();
	}
}


void Department::addCreature(int creatureID, int magiID, int level){
	try{
		Magizoologist* magi = this->magis->find(magiID)->getInfo();

		if(magi->getCreaturesById()->find(creatureID) != NULL){
			throw new CreatureIDAlreadyExistsException();
		}

		Creature* crea = new Creature(level,magi,NULL,NULL);
		magi->addCreature(crea,creatureID);

		AVLTree<Creature, int>* byid = magi->getCreaturesById()->find(creatureID);
		AVLTree<Creature, levelKey>* bylevel = magi->getCreaturesByLevel()->find(new levelKey(level,creatureID));

		crea->setById(byid);
		crea->setByLevel(bylevel);

		this->creatures = this->creatures->insert(crea,creatureID);
	}
	catch(AVLTree<Magizoologist, int>::NotFoundException*){
		throw new MagiIDNotFoundException();
	}
	catch(AVLTree<Creature, int>::AlreadyExistsException*){
		throw new CreatureIDAlreadyExistsException();
	}
	catch(...){
		throw;
	}
}


void Department::releaseCreature(int creatureID){

}


void Department::replaceMagizoologist(int magiID, int replacementID){

}


void Department::increaseLevel(int creatureID, int delta){
}


void Department::getMostDangerous(int magiID, int* creatureID){
	//Magizoologist* magi = this->magis->find(magiID)->getInfo();

}


void Department::getAllCreaturesByLevel(int magiID, int** creatures, int* numOfCreatures){
}


Department::~Department(){
	delete creatures;
	delete magis;
}
