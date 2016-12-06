/*
 * Magizoologist.cpp
 *
 *  Created on: 5 áãöî× 2016
 *      Author: Liron
 */

#include "Magizoologist.h"


Magizoologist::Magizoologist(){
	creaturesById = new AVLTree<Creature, int>();
	creaturesByLevel = new AVLTree<Creature, levelKey>();
	mostDangerous = NULL ;
	mostDangerousID = -1;

}

AVLTree<Creature, int>* Magizoologist::getCreaturesById(){
	return this->creaturesById;
}

AVLTree<Creature, levelKey>* Magizoologist::getCreaturesByLevel(){
	return this->creaturesByLevel;
}


void Magizoologist::addCreature(Creature* creature, int id){
	creaturesById = creaturesById->insert(creature, id);
	creature->setById(creaturesById->find(id));
	levelKey lk = levelKey(creature->getLevel(), id);
	creaturesByLevel = creaturesByLevel->insert(creature, lk);
	creature->setByLevel(creaturesByLevel->find(lk));
	if(mostDangerous == NULL){
		mostDangerous = creature;
		mostDangerousID = id;
	}
	else if(creature->getLevel() >= this->mostDangerous->getLevel() &&
			this->mostDangerousID >= id){
		this->mostDangerous = creature;
		mostDangerousID = id;
	}
}

/*
 * find the creature in the main DS
 * go to its owner
 * delete it from its tree
 */
//TODO: this isn't supposed to be called from magizoologist
void Magizoologist::releaseCreature(int id){
	Creature* creature = (creaturesById->find(id))->getInfo();
	creature->setMagizoologist(NULL);
	creaturesById = creaturesById->remove(id);
	if(creature == this->mostDangerous)
		this->mostDangerous = creature->getByLevel()->getParent()->getInfo();	// TODO: important to use
	levelKey lk = levelKey(creature->getLevel(),id);
	creaturesByLevel = creaturesByLevel->remove(lk);
}


static int** flip(int** creatures, int* numOfCreatures){
	int** res = (int**)malloc(sizeof(int*)*(*numOfCreatures));
	for(int i=0; i<*numOfCreatures; i++){
		res[i] = creatures[*numOfCreatures-i-1];
	}
	return res;
}


void Magizoologist::getAllCreaturesByLevel(int** creatures, int* numOfCreatures)
{
	*numOfCreatures = creaturesByLevel->getSize();
	levelKey* lks = (levelKey*)malloc(sizeof(levelKey)*(*numOfCreatures));
	creaturesByLevel->turnToArrays(lks, NULL);
	for(int i=0; i<*numOfCreatures; i++){
		*creatures[i] = lks[i].level;
	}
	creatures = flip(creatures, numOfCreatures);
	free(lks);
}

void Magizoologist::ReplaceMagizoologist(Magizoologist rep){
	if(this->creaturesById->getSize() == 0) return;

	int thisSize = this->creaturesById->getSize(),
			repSize = rep.creaturesById->getSize();
	Creature** idInfo1 = new Creature*[thisSize];
	Creature** levelInfo1 = new Creature*[thisSize];
	int* idIndex1 = new int[thisSize];
	levelKey* levelIndex1 = new levelKey[thisSize];

	this->creaturesById->turnToArrays(idIndex1,idInfo1);
	this->creaturesByLevel->turnToArrays(levelIndex1,levelInfo1);

	delete this->creaturesById;
	this->creaturesById = new AVLTree<Creature, int>();
	delete this->creaturesByLevel;
	this->creaturesByLevel = new AVLTree<Creature, levelKey>();

	Creature** idInfo2 = new Creature*[repSize];
	Creature** levelInfo2 = new Creature*[repSize];
	int* idIndex2 = new int[repSize];
	levelKey* levelIndex2 = new levelKey[repSize];

	rep.creaturesById->turnToArrays(idIndex2,idInfo2);
	rep.creaturesByLevel->turnToArrays(levelIndex2,levelInfo2);

	delete rep.creaturesById;
	delete rep.creaturesByLevel;

	for(int i=0;i<thisSize;i++){
		idInfo1[i]->setMagizoologist(&rep);
		levelInfo1[i]->setMagizoologist(&rep);
	}

	Creature** idinfo=NULL ;
	int* idindex=NULL ;
	Marge<int>(idInfo1,idIndex1,thisSize,idInfo2,idIndex2,repSize,idinfo,idindex);

	rep.creaturesById->fillFromArray(idindex,idinfo,thisSize+repSize);

	Creature** levelinfo=NULL ;
	levelKey* levelindex=NULL ;
	Marge<levelKey>(levelInfo1,levelIndex1,thisSize,levelInfo2,levelIndex2,repSize,levelinfo,levelindex);

	rep.creaturesByLevel->fillFromArray(levelindex,levelinfo,thisSize+repSize);

	delete idInfo1;
	delete idInfo2;
	delete levelInfo1;
	delete levelInfo2;
	delete idIndex1;
	delete idIndex2;
	delete levelIndex1;
	delete levelIndex2;
	delete idinfo;
	delete idindex;
	delete levelinfo;
	delete levelindex;
}




Magizoologist::~Magizoologist(){
	delete creaturesByLevel;
	delete creaturesById;
}

