/*
 * Department.c
 *
 *  Created on: 5 áãöî× 2016
 *      Author: Liron
 */
#include "Department.h"

/*
 * TODO s:
 * -check that adding a creature gives it pointers to both nodes
 * -test this ship out
 */

Department::Department() :
magis(new AVLTree<Magizoologist, int>()), creatures(new AVLTree<Creature, int>()),
creaturesByLevel(new AVLTree<Creature, levelKey>()), mostDangerous(NULL), mostDangerousId(-1){

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
	catch(...){
		throw;
	}
}


void Department::addCreature(int creatureID, int magiID, int level){
	if(this == NULL || creatureID <= 0 || magiID <= 0 || level < 0 ){
		throw InvalidInputException();
	}
	try{
		Magizoologist* magi = this->magis->find(magiID)->getInfo();
		if(magi == NULL)
			throw MagiIDNotFoundException();

		AVLTree<Creature, int>* temp1 = magi->getCreaturesById()->find(creatureID);
		AVLTree<Creature, int>* temp2 = creatures->find(creatureID);
		if(temp1 != NULL || temp2 != NULL){
			throw CreatureIDAlreadyExistsException();
		}

		Creature* crea = new Creature(level,magi,NULL,NULL);
		this->creatures = this->creatures->insert(crea,creatureID);
		this->creaturesByLevel = this->creaturesByLevel->insert(crea, levelKey(level, creatureID));
		magi->addCreature(crea,creatureID);

		AVLTree<Creature, int>* byid = magi->getCreaturesById()->find(creatureID);
		AVLTree<Creature, levelKey>* bylevel = magi->getCreaturesByLevel()->find(levelKey(level,creatureID));

		crea->setById(byid);
		crea->setByLevel(bylevel);

		// update department's most dangerous creature
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
		AVLTree<Creature, int>* pointer = this->creatures->find(creatureID);
		if(pointer == NULL)
			throw CreatureIDNotFoundException();

		Creature* creature = pointer->getInfo();
		if(creatureID == mostDangerousId)		// update department's most dangerous if needed
			this->updateMostDangerous();

		Magizoologist* magi = creature->getMagizoologist();
		if(magi->getMostDangerous() == creature)
			magi->updateMostDangerous();		// update department's most dangerous if needed

		// i hate you so much for this >:C
		magi->releaseCreature(creatureID);

		// remove the creature from the department's trees
		creatures = creatures->remove(creatureID);
		creaturesByLevel = creaturesByLevel->remove(levelKey(creature->getLevel(), creatureID));

		delete creature;
	}
	catch(AVLTree<Creature, int>::NotFoundException*){
		throw CreatureIDNotFoundException();
	}
	catch(...){
		throw;
	}
}


void Department::replaceMagizoologist(int magiID, int replacementID){
	if(magiID<=0 || this == NULL || replacementID<=0 || magiID == replacementID){
		throw InvalidInputException();
	}
	try{
		Magizoologist* magi1 = this->magis->find(magiID)->getInfo();
		Magizoologist* magi2 = this->magis->find(replacementID)->getInfo();

		if(magi1 == NULL || magi2 == NULL)
			throw MagiIDNotFoundException();

		magi1->ReplaceMagizoologist(magi2);

		this->magis =  this->magis->remove(magiID);
		delete magi1;

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
		AVLTree<Creature,int>* creatureTree = this->creatures->find(creatureID);
		if(creatureTree == NULL){
			throw CreatureIDNotFoundException();
		}
		Creature* creature = creatureTree->getInfo();
		Magizoologist* magi = creature->getMagizoologist();
		magi->creaturesByLevel = magi->creaturesByLevel->remove(levelKey(creature->getLevel(),creatureID));
		creature->increaseLevel(delta);
		levelKey lk = levelKey(creature->getLevel(), creatureID);
		magi->creaturesByLevel = magi->creaturesByLevel->insert(creature, lk);
		if(magi->getMostDangerous()->getByLevel()->getIndex() < lk){
			magi->setMostDangerousID(creatureID);
			magi->setMostDangerous(creature);
		}
		if(this->mostDangerous->getByLevel()->getIndex() < lk){
			this->mostDangerous = creature;
			this->mostDangerousId = creatureID;
		}
		creature->setByLevel(magi->getCreaturesByLevel()->find(lk));
	}
	catch(AVLTree<Creature, int>::NotFoundException&){
		throw CreatureIDNotFoundException();
	}
	catch(...){
		throw;
	}
}


void Department::getMostDangerous(int magiID, int* creatureID){
	if(this == NULL || creatureID == NULL || magiID == 0){
		throw InvalidInputException();
	}
	if(magiID < 0){
		*creatureID = mostDangerousId;
		return;
	}
	try{
		AVLTree<Magizoologist, int>* pointer = magis->find(magiID);
		if(pointer == NULL)
			throw MagiIDNotFoundException();
		Magizoologist* magi = pointer->getInfo();
		*creatureID = magi->getMostDangerousID();
	}
	catch(AVLTree<Magizoologist, int>::NotFoundException*){
		throw MagiIDNotFoundException();
	}
	catch(...){
		throw;
	}
}


void Department::getAllCreaturesByLevel(int magiID, int** creatures, int* numOfCreatures){
	if(this == NULL || magiID == 0 || creatures == NULL || numOfCreatures == NULL){
		throw InvalidInputException();
	}
	if(magiID < 0){		// should be all creatures ordered by level and id
		levelKey* keys = new levelKey[creaturesByLevel->getSize()];
		if(keys == NULL){
			throw AllocationErrorException();
		}
		this->creaturesByLevel->turnToArrays(keys, NULL);	// we don't need the creatures themselves
		*numOfCreatures = creaturesByLevel->getSize();
		if(*numOfCreatures == 0){
			delete keys;
			*creatures = NULL;
			return;
		}
		int* indexes = (int*)malloc(sizeof(int)*(*numOfCreatures));
		if(indexes == NULL){
			free(keys);
			throw AllocationErrorException();
		}
		for(int i=0; i<*numOfCreatures; i++){
			indexes[i] = keys[i].id;	// should be public
		}
		flip(indexes, *numOfCreatures);
		*creatures = indexes;
		delete keys;
		return;

	}
	try{
		Magizoologist* magi = this->magis->find(magiID)->getInfo();
		if(magi == NULL)
			throw MagiIDNotFoundException();
		magi->getAllCreaturesByLevel(creatures, numOfCreatures);
	}
	catch(AVLTree<Magizoologist, int>::NotFoundException& e){
		throw MagiIDNotFoundException();
	}
	catch(Magizoologist::MagiAllocationErrorException& e){
		throw AllocationErrorException();

	}
	catch(...){
		throw;
	}
}


void Department::updateMostDangerous(){
	if(this == NULL)
		return ;
	if(mostDangerous->getByLevel()->getParent() == NULL){
		if(mostDangerous->getByLevel()->getLeft() != NULL){
			this->mostDangerous = mostDangerous->getByLevel()->getLeft()->getInfo();
			this->mostDangerousId = mostDangerous->getByLevel()->getIndex().id;
			return;
		}
		this->mostDangerous = NULL;
		this->mostDangerousId = -1;
		return;
	}
	this->mostDangerous = mostDangerous->getByLevel()->getParent()->getInfo();
	this->mostDangerousId = mostDangerous->getByLevel()->getIndex().id;
}


Magizoologist* Department::getMagi(int id){
	return magis->find(id)->getInfo();
}


Department::~Department(){
	this->creatures->Quit();
	magis->QuitALL();
	creaturesByLevel->QuitALL();
}
