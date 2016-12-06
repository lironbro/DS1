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

Department::Department() :
magis(new AVLTree<Magizoologist, int>()), creatures(new AVLTree<Creature, int>()),
		mostDangerous(NULL), mostDangerousId(-1){

}


void Department::addMagizoologist(int id){
	if(this == NULL || id <= 0 ){
		throw InvalidInputException();
	}
	try{
		magis = magis->insert(new Magizoologist(), id);
	}
	catch(AVLTree<Magizoologist, int>::AlreadyExistsException& e){
		throw MagiIDAlreadyExistsException();
	}
}


void Department::addCreature(int creatureID, int magiID, int level){
	if(this == NULL || creatureID <= 0 || magiID <= 0 || level < 0 ){
		throw InvalidInputException();
	}
	try{
		Magizoologist* magi = this->magis->find(magiID)->getInfo();

		if(magi->getCreaturesById()->find(creatureID) != NULL){
			throw CreatureIDAlreadyExistsException();
		}

		Creature* crea = new Creature(level,magi,NULL,NULL);
		magi->addCreature(crea,creatureID);

		AVLTree<Creature, int>* byid = magi->getCreaturesById()->find(creatureID);
		AVLTree<Creature, levelKey>* bylevel = magi->getCreaturesByLevel()->find(levelKey(level,creatureID));

		crea->setById(byid);
		crea->setByLevel(bylevel);

		this->creatures = this->creatures->insert(crea,creatureID);

		// update most dangerous creature
		if(mostDangerousId == -1){
			this->mostDangerous = crea;
			this->mostDangerousId = creatureID;
		}
		else{
			if(crea->getLevel() > mostDangerous->getLevel() ||
					(crea->getLevel() == mostDangerous->getLevel() &&
							creatureID < mostDangerousId)){
				mostDangerousId = creatureID;
				mostDangerous = crea;
			}
		}

	}
	catch(AVLTree<Magizoologist, int>::NotFoundException*){
		throw MagiIDNotFoundException();
	}
	catch(AVLTree<Creature, int>::AlreadyExistsException*){
		throw CreatureIDAlreadyExistsException();
	}
	catch(...){
		throw;
	}
}


void Department::releaseCreature(int creatureID){
	if(this == NULL || creatureID <= 0){
		throw InvalidInputException();
	}
	try{
		Creature* creature = this->creatures->find(creatureID)->getInfo();
		Magizoologist* magi = creature->getMagizoologist();
		if(magi->getMostDangerous() == creature)
			magi->updateMostDangerous();		// set most dangerous to be its parent in the level tree
		creature->getById()->remove(creatureID);
		creature->getByLevel()->remove(levelKey(creature->getLevel(), creatureID));
		// the previous two lines cause the nodes to remove themselves from the magi's trees
		// everything other than actions on creatures should be O(1)
		creatures->remove(creatureID);
		//delete creature;		//TODO: this is probably pointless, delete it when you have the time
	}
	catch(AVLTree<Creature, int>::NotFoundException*){
		throw CreatureIDNotFoundException();
	}
	catch(...){
		throw;
	}
}


// Tal's rensponsibility lol
void Department::replaceMagizoologist(int magiID, int replacementID){
	try{
		Magizoologist* magi1 = this->magis->find(magiID)->getInfo();
		Magizoologist* magi2 = this->magis->find(replacementID)->getInfo();

		magi1->ReplaceMagizoologist(*magi2);

	}
	catch(...){
		throw;
	}
}


// TODO: have Tal look at this
void Department::increaseLevel(int creatureID, int delta){
	if(this == NULL || creatureID <= 0 || delta <= 0){
		throw InvalidInputException();
	}
	try{
		Creature* creature = this->creatures->find(creatureID)->getInfo();
		Magizoologist* magi = creature->getMagizoologist();
		magi->getCreaturesByLevel()->remove(creatureID);
		// TODO: removing from the tree might also delete the object / AVLTree node, which is bad
		creature->increaseLevel(delta);
		magi->getCreaturesByLevel()->insert(creature, levelKey(creature->getLevel(), creatureID));
	}
	catch(AVLTree<Creature, int>::NotFoundException*){
		throw CreatureIDNotFoundException();
	}
	catch(...){
		throw;
	}
}


// TODO: have Tal look at this
void Department::getMostDangerous(int magiID, int* creatureID){
	if(this == NULL || creatureID == NULL || magiID == 0){
		throw InvalidInputException();
	}
	if(magiID < 0){
		*creatureID = mostDangerousId;
		return;
	}
	try{
		Magizoologist* magi = this->magis->find(magiID)->getInfo();
		*creatureID = magi->getMostDangerousID();
	}
	catch(AVLTree<Magizoologist, int>::NotFoundException*){
		throw MagiIDNotFoundException();
	}
	catch(...){
		throw;
	}
}


// TODO: have Tal look at this, maybe make it his responsibility?
// TODO: add code for when magiID < 0, should return all creatures
void Department::getAllCreaturesByLevel(int magiID, int** creatures, int* numOfCreatures){
	if(this == NULL || magiID == 0 || creatures == NULL || numOfCreatures == NULL){
		throw InvalidInputException();
	}
	try{
		Magizoologist* magi = this->magis->find(magiID)->getInfo();
		magi->getAllCreaturesByLevel(creatures, numOfCreatures);
	}
	catch(AVLTree<Magizoologist, int>::NotFoundException*){
		throw MagiIDNotFoundException();
	}
	catch(...){
		throw;
	}
}


Department::~Department(){
	delete creatures;
	delete magis;
}
