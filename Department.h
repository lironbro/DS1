/*
 * Department.h
 *
 *  Created on: 5 בדצמ× 2016
 *      Author: Liron
 */

#ifndef DEPARTMENT_H_
#define DEPARTMENT_H_


#include "Magizoologist.h"

class Department{



private:
	AVLTree<Magizoologist, int>* magis;
	AVLTree<Creature, int>* creatures;


public:


	Department();


	void addMagizoologist(int id);


	void addCreature(int creatureID, int magiID, int level);


	void releaseCreature(int creatureID);


	void replaceMagizoologist(int magiID, int replacementID);


	void increaseLevel(int creatureID, int delta);


	void getMostDangerous(int magiID, int* creatureID);


	void getAllCreaturesByLevel(int magiID, int** creatures, int* numOfCreatures);


	~Department();

};

#endif /* DEPARTMENT_H_ */
