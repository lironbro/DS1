/*
 * Magizoologist.h
 *
 *  Created on: 5 áãöî× 2016
 *      Author: Liron
 */

#ifndef MAGIZOOLOGIST_H_
#define MAGIZOOLOGIST_H_


#include "AVLTree.h"
#include "Creature.h"



class Magizoologist{

public:


	AVLTree<Creature, int>* creaturesById;
	AVLTree<Creature, levelKey>* creaturesByLevel;
	Creature* mostDangerous;
	int mostDangerousID;


public:



	class MagiAllocationErrorException : public std::exception{};



	Magizoologist();


	void addCreature(Creature* creature, int id);	// TODO: check this when not stupid


	void releaseCreature(int id);


	Creature* getMostDangerous();


	void updateMostDangerous();


	int getMostDangerousID();


	void getAllCreaturesByLevel(int** creatures, int* numOfCreatures);


	void ReplaceMagizoologist(Magizoologist* rep);


	AVLTree<Creature, int>* getCreaturesById();


	AVLTree<Creature, levelKey>* getCreaturesByLevel();


	~Magizoologist();
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
		if(this == NULL){		// if this happens, something got messed up
			return false;
		}
		return this->level == key.level && this->id == key.id;
	}

	bool operator!=(levelKey key){
		return !(*this == key);
	}

	bool operator<=(levelKey key){
		if(this->level < key.level)
			return true;
		if(this->level == key.level && this->id > key.id)
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





template<class T>
void Merge(Creature** A1,T* A2,int sizeA,Creature** B1,T* B2,int sizeB
		,Creature*** cratures ,T** indexes)
{
	int iA=0,iB=0,i=0;
	*cratures = new Creature*[sizeA+sizeB];
	*indexes  = new T[sizeA+sizeB];
	while(iA<sizeA && iB<sizeB){
		if(A2[iA]<B2[iB]){
			(*cratures)[i]=A1[iA];
			(*indexes)[i]=A2[iA];
			iA++;
		}else{
			(*cratures)[i]=B1[iB];
			(*indexes)[i]=B2[iB];
			iB++;
		}
		i++;
	}
	while(iA<sizeA) {
		(*cratures)[i]=A1[iA];
		(*indexes)[i++]=A2[iA++];
	}
	while(iB<sizeB) {
		(*cratures)[i]=B1[iB];
		(*indexes)[i++]=B2[iB++];
	}
}


static void flip(int* a, int n){
	for(int i=0; i<n/2; i++){
		int temp = a[i];
		a[i] = a[n - i - 1];
		a[n - i -1] = temp;
	}
}

#endif /* MAGIZOOLOGIST_H_ */
