/*
 * Magizoologist.cpp
 *
 *  Created on: 5 בדצמ× 2016
 *      Author: Liron
 */

#include "Magizoologist.h"


Magizoologist::Magizoologist(){
	creaturesById = new AVLTree<Creature, int>();
	creaturesByLevel = new AVLTree<Creature, levelKey>();
	mostDangerous = NULL ;
	mostDangerousID = -1;

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


Magizoologist::~Magizoologist(){
	delete creaturesByLevel;
	delete creaturesById;
}





