/*
 * Creatures.cpp
 *
 *  Created on: 5 áãöî× 2016
 *      Author: Liron
 */

#include "Creature.h"

Creature::Creature(int dangerLevel, Magizoologist* magi,
		AVLTree<Creature, int>* byId, AVLTree<Creature, levelKey>* byLevel ):
		level(dangerLevel), magi(magi), byId(byId), byLevel(byLevel){

}

int Creature::getLevel(){
	if(this == NULL)
		return -1;
	return level;
}

void Creature::increaseLevel(int delta){
	if(this == NULL)
		return ;
	level += delta;
}

Magizoologist* Creature::getMagizoologist(){
	if(this == NULL)
		return NULL;
	return this->magi;
}

void Creature::setMagizoologist(Magizoologist* magi){
	if(this == NULL)
		return;
	this->magi = magi;
}

AVLTree<Creature, int>* Creature::getById(){
	if(this == NULL)
		return NULL;
	return byId;
}

void Creature::setById(AVLTree<Creature, int>* byId){
	if(this == NULL)
		return ;
	this->byId = byId;
}

AVLTree<Creature, levelKey>* Creature::getByLevel(){
	if(this == NULL)
		return NULL;
	return byLevel;
}

void Creature::setByLevel(AVLTree<Creature, levelKey>* byLevel){
	if(this == NULL)
		return ;
	this->byLevel = byLevel;
}
