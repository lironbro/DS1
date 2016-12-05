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
}


void Magizoologist::releaseCreature(int id){
	Creature* creature = (creaturesById->find(id))->getInfo();
	creature->setMagizoologist(NULL);
	creaturesById = creaturesById->remove(id);
	levelKey lk = levelKey(creature->getLevel(),id);
	creaturesByLevel = creaturesByLevel->remove(lk);
}


void Magizoologist::getAllCreaturesByLevel(int** creatures, int* numOfCreatures)
{

}


