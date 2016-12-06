/*
 * Department.c
 *
 *  Created on: 5 בדצמ× 2016
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

Department::Department() : magis(), creatures(){

}


void Department::addMagizoologist(int id){
	magis->insert(new Magizoologist(), id);
}


void Department::addCreature(int creatureID, int magiID, int level){
	Creature* creature = new Creature(level, NULL);
	creatures->insert(creature, creatureID);
	Magizoologist* magi = magis->find(magiID)->getInfo();
	if(magi == NULL)
	{
		//TODO: throw exception
	}
	magi->addCreature(creature, creatureID);
	// add the byId and byKey pointers for creature
	creature->setById(magi->creaturesById->find(creatureID));	//TODO: check this out
	creature->setByLevel(magi->creaturesByLevel->find(creatureID));
}


void Department::releaseCreature(int creatureID){

}


void Department::replaceMagizoologist(int magiID, int replacementID){

}


void Department::increaseLevel(int creatureID, int delta){
	Creature* creature = this->creatures;
}


void Department::getMostDangerous(int magiID, int* creatureID){
	Magizoologist* magi = this->magis->find(magiID)->getInfo();

	*(creatureID) = magi->getMostDangerous();
}


void Department::getAllCreaturesByLevel(int magiID, int** creatures, int* numOfCreatures){
	Magizoologist* magi = this->magis->find(magiID);
	magi->getAllCreaturesByLevel(creatures, numOfCreatures);
}


Department::~Department(){
	delete creatures;
	delete magis;
}

