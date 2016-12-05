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


}


void Magizoologist::addCreature(int id, int level){
	Creature* creature = new Creature(level, this);
	creaturesById = creaturesById->insert(creature, id);
	creature->setById(creaturesById->find(id));
	levelKey lk = levelKey(level, id);
	creaturesByLevel = creaturesByLevel->insert(creature, lk);
	creature->setByLevel(creaturesByLevel->find(lk));
	if(creature >= *(this->mostDangerous))		// TODO: pointers will be bad
		this->mostDangerous = creature;
}

//TODO: this isn't supposed to be called from magizoologist
void Magizoologist::releaseCreature(int id){
	Creature* creature = (creaturesById->find(id))->getInfo();
	creature->setMagizoologist(NULL);
	creaturesById = creaturesById->remove(id);
	if(creature == this->mostDangerous)
		this->mostDangerous = creature->byLevel->getParent()->getInfo();	// TODO: important
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





