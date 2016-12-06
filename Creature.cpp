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
	return level;
}

void Creature::increaseLevel(int delta){
	level += delta;
}

Magizoologist* Creature::getMagizoologist(){
	return this->magi;
}

void Creature::setMagizoologist(Magizoologist* magi){
	this->magi = magi;
}

AVLTree<Creature, int>* Creature::getById(){
	return byId;
}

void Creature::setById(AVLTree<Creature, int>* byId){
	this->byId = byId;
}

AVLTree<Creature, levelKey>* Creature::getByLevel(){
	return byLevel;
}

void Creature::setByLevel(AVLTree<Creature, levelKey>* byLevel){
	this->byLevel = byLevel;
}
