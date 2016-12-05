/*
 * Magizoologist.h
 *
 *  Created on: 5 בדצמ× 2016
 *      Author: Liron
 */

#ifndef MAGIZOOLOGIST_H_
#define MAGIZOOLOGIST_H_


#include "AVLTree.h"
#include "Creature.h"



class Magizoologist{

private:


	AVLTree<Creature, int>* creaturesById;
	AVLTree<Creature, levelKey>* creaturesByLevel;
	Creature* mostDangerous;


public:

	Magizoologist();


	void addCreature(int level, int id);


	void releaseCreature(int id);


	void getMostDangerous();


	void getAllCreaturesByLevel(int** creatures, int* numOfCreatures);
};


class levelKey{
public:

	int level;
	int id;

	levelKey(int level, int id){
		this->level = level;
		this->id = id;
	}

	levelKey(){
		this->level = -1;
		this->id = -1;
	}

	bool operator==(levelKey key){
		return this->level == key.level && this->id == key.id;
	}

	bool operator!=(levelKey key){
		return !(*this == key);
	}

	bool operator<=(levelKey key){
		if(this->level < key.level)
			return true;
		if(this->id >= key.id)
			return true;
		return false;
	}

	bool operator<(levelKey key){
		return *this <= key && !(*this == key);
	}

	bool operator>=(levelKey key){
		return !(*this<key);
	}

	bool operator>(levelKey key){
		return *this >= key && !(*this == key);
	}

	levelKey(bool i){
		if(!i){
			level =-1;
			id = -1;
		}
	}

};


#endif /* MAGIZOOLOGIST_H_ */

