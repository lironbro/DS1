/*
 * Creature.h
 *
 *  Created on: 5 בדצמ× 2016
 *      Author: Liron
 */

#ifndef CREATURE_H_
#define CREATURE_H_

#include <stdio.h>			// TODO: find out how bad of a choice this was
#include "AVLTree.h"

class Magizoologist;
class levelKey;


class Creature{




private:
	int level;
	Magizoologist* magi;
	AVLTree<Creature, int>* byId;
	AVLTree<Creature, levelKey>* byLevel;


public:

	Creature(int dangerLevel = 0, Magizoologist* magi = NULL,
			AVLTree<Creature, int>* byId = NULL, AVLTree<Creature, levelKey>* byLevel = NULL);

	int getLevel();

	void setLevel(int dangerLevel);

	Magizoologist* getMagizoologist();

	void setMagizoologist(Magizoologist* magi);

	AVLTree<Creature, int>* getById();

	void setById(AVLTree<Creature, int>* byId);

	AVLTree<Creature, levelKey>* getByLevel();

	void setByLevel(AVLTree<Creature, levelKey>* byLevel);
};


#endif /* CREATURE_H_ */
