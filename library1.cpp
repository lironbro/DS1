/*
 * library1.cpp
 *
 *  Created on: 6 בדצמ 2016
 *      Author: user
 */

#include"library1.h"
#include"Department.h"
#include <iostream>


void* Init() {
	Department * DS = new Department();
	return (void*)DS;
}

StatusType AddMagizoologist(void *DS, int MagiID){
	if(DS == NULL){
		return INVALID_INPUT;
	}
	try{
		((Department*)DS)->addMagizoologist(MagiID);
		return SUCCESS;
	}
	catch(std::bad_alloc&){
		return ALLOCATION_ERROR;
	}
	catch(Department::InvalidInputException&){
		return INVALID_INPUT;
	}
	catch(Department::MagiIDAlreadyExistsException&){
		return FAILURE;
	}

}

StatusType AddCreature(void *DS, int creatureID, int magiID, int level){
	if(DS == NULL){
		return INVALID_INPUT;
	}
	try{
		((Department*)DS)->addCreature(creatureID,magiID,level);
		return SUCCESS;
	}
	catch(std::bad_alloc&){
		return ALLOCATION_ERROR;
	}
	catch(Department::InvalidInputException&){
		return INVALID_INPUT;
	}
	catch(Department::MagiIDNotFoundException&){
		return FAILURE;
	}
	catch(Department::CreatureIDAlreadyExistsException&){
		return FAILURE;
	}

}

StatusType ReleaseCreature(void *DS, int creatureID){
	if(DS == NULL){
		return INVALID_INPUT;
	}
	try{
		((Department*)DS)->releaseCreature(creatureID);
		return SUCCESS;
	}
	catch(Department::InvalidInputException&){
		return INVALID_INPUT;
	}
	catch(Department::CreatureIDNotFoundException&){
		return FAILURE;
	}

}

StatusType ReplaceMagizoologist(void *DS, int MagiID, int ReplacementID){
	if(DS == NULL){
		return INVALID_INPUT;
	}
	try{
		((Department*)DS)->replaceMagizoologist(MagiID,ReplacementID);
		return SUCCESS;
	}
	catch(Department::InvalidInputException&){
		return INVALID_INPUT;
	}
	catch(std::bad_alloc&){
		return ALLOCATION_ERROR;
	}
	catch(Department::MagiIDNotFoundException&){
		return FAILURE;
	}
}

StatusType IncreaseLevel(void *DS, int creatureID, int levelIncrease){
	if(DS == NULL){
		return INVALID_INPUT;
	}
	try{
		((Department*)DS)->increaseLevel(creatureID,levelIncrease);
		return SUCCESS;
	}
	catch(Department::InvalidInputException&){
		return INVALID_INPUT;
	}
	catch(std::bad_alloc&){
		return ALLOCATION_ERROR;
	}
	catch(Department::CreatureIDNotFoundException&){
		return FAILURE;
	}
}

StatusType GetMostDangerous(void *DS, int magiID, int *creatureID){
	if(DS == NULL){
		return INVALID_INPUT;
	}
	try{
		((Department*)DS)->getMostDangerous(magiID,creatureID);
		return SUCCESS;
	}
	catch(Department::InvalidInputException&){
		return INVALID_INPUT;
	}
	catch(std::bad_alloc&){
		return ALLOCATION_ERROR;
	}
}

StatusType GetAllCreaturesByLevel(void *DS, int magiID, int **creatures, int *numOfCreatures){
	if(DS == NULL){
		return INVALID_INPUT;
	}
	try{
		((Department*)DS)->getAllCreaturesByLevel(magiID,creatures,numOfCreatures);
		return SUCCESS;
	}
	catch(Department::InvalidInputException&){
		return INVALID_INPUT;
	}
	catch(std::bad_alloc&){
		return ALLOCATION_ERROR;
	}
}

void Quit(void** DS){

}


