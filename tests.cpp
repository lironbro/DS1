/*
 * test_BinTree.cpp
 *
 *  Created on: 27 áðåá× 2016
 *      Author: Liron
 */

#include "Department.h"


bool addMagizoologistTest(Department* d){


	// addMagizoologist test
	d->addMagizoologist(55);
	d->addMagizoologist(32);
	d->addMagizoologist(123);		// this guy should be empty the entire test
	try{
		d->addMagizoologist(32);
	}
	catch(Department::MagiIDAlreadyExistsException& e){

	}
	catch(...){
		return false;
	}
	try{
		d->addMagizoologist(-1);
	}
	catch(Department::InvalidInputException& e){

	}
	catch(...){
		return false;
	}

	return true;
}


bool addCreatureTest(Department* d){

	// addCreature test
	d->addCreature(5,55,8);		// should be initial most dangerous
	try{
		d->addCreature(5,55,9);		// should throw id already exists exception
	}
	catch(Department::CreatureIDAlreadyExistsException& e){

	}
	catch(...){
		return false;
	}
	d->addCreature(10,55,8);	// this shouldn't be the most dangerous
	d->addCreature(3,55,3);
	d->addCreature(2,55,3);		// should be more dangerous than the previous line
	d->addCreature(1000,55,5);

	d->addCreature(500,32,100);
	d->addCreature(501,32,100);
	d->addCreature(499,32,100);
	d->addCreature(502,32,150);		// should be the most dangerous under 32
	d->addCreature(503,32,20);
	try{
		d->addCreature(1000,32,150);
	}
	catch(Department::MagiIDAlreadyExistsException& e){

	}
	catch(...){
		return false;
	}
	try{
		d->addCreature(1000, 666, 1);
	}
	catch(Department::MagiIDNotFoundException& e){

	}
	catch(...){
		return false;
	}
	try{
		d->addCreature(-1000, 32, 1);		// negative creatureid
	}
	catch(Department::InvalidInputException& e){

	}
	catch(...){
		return false;
	}
	try{
		d->addCreature(1000, -32, 1);		// negative magiid
	}
	catch(Department::InvalidInputException& e){

	}
	catch(...){
		return false;
	}
	try{
		d->addCreature(1000, 32, 0);		// nonpositive level
	}
	catch(Department::InvalidInputException& e){

	}
	catch(...){
		return false;
	}
	try{
		d->addCreature(1000, 32, -1);		// nonpositive level
	}
	catch(Department::InvalidInputException& e){

	}
	catch(...){
		return false;
	}



	return true;
}


bool releaseCreatureTest(Department* d){



	// releaseCreature test
	d->releaseCreature(5);
	try{
		d->releaseCreature(5);
	}
	catch(Department::CreatureIDNotFoundException& e){

	}
	catch(...){
		return false;
	}
	try{
		d->releaseCreature(1337);
	}
	catch(Department::CreatureIDNotFoundException& e){

	}
	catch(...){
		return false;
	}
	try{
		d->releaseCreature(-10);			// negative id
	}
	catch(Department::InvalidInputException& e){

	}
	catch(...){
		return false;
	}

	return true;
}


bool replaceMagizoologistTest(Department* d){

	// ReplaceMagizoologist test


	return true;
}



bool increaseLevelTest(Department* d){


	// increaseLevel test
	d->increaseLevel(500, 100);		// now 500 should be the most dangerous under 32
	try{
		d->increaseLevel(-666, 100);		// negative id
	}
	catch(Department::InvalidInputException& e){

	}
	catch(...){
		return false;
	}
	try{
		d->increaseLevel(666, 100);			// no creatureid
	}
	catch(Department::CreatureIDNotFoundException& e){

	}
	catch(...){
		return false;
	}


	return true;
}



bool getMostDangerousTest(Department* d){


	// getMostDangerous test
	int* dangerous = (int*)malloc(sizeof(*dangerous));		//TODO: is malloc good for this?
	d->getMostDangerous(32, dangerous);		// dangerous should point to 500
	d->getMostDangerous(55, dangerous);		// dangerous should point to 2
	d->getMostDangerous(123, dangerous);	// dangerous should point to be -1
	d->getMostDangerous(-1000, dangerous);	// dangerous should point to 500
	try{
		d->getMostDangerous(666, dangerous);		// no magi id

	}
	catch(Department::MagiIDNotFoundException& e){

	}
	catch(...){
		return false;
	}
	try{
		d->getMostDangerous(-666, dangerous);		// negative id

	}
	catch(Department::InvalidInputException& e){

	}
	catch(...){
		return false;
	}
	try{
		d->getMostDangerous(123, NULL);		// null pointer

	}
	catch(Department::InvalidInputException& e){

	}
	catch(...){
		return false;
	}

	return true;
}



bool getAllCreaturesByLevelTest(Department* d){


	// getAllCreaturesByLevel test
	int* numOfCreatures = new int;
	int* creatureArray;						// TODO: this is annoying, maybe this is good?
	int** creatures = &creatureArray;		// TODO: is this the way to do this? who knows?
	d->getAllCreaturesByLevel(-1, creatures, numOfCreatures); 	// should return all creatures
	d->getAllCreaturesByLevel(32, creatures, numOfCreatures);
	d->getAllCreaturesByLevel(123, creatures, numOfCreatures);		// creatures should be NULL, num should be 0
	try{
		d->getAllCreaturesByLevel(123, NULL, numOfCreatures);
	}
	catch(Department::InvalidInputException& e){

	}
	catch(...){
		return false;
	}
	try{
		d->getAllCreaturesByLevel(123, creatures, NULL);
	}
	catch(Department::InvalidInputException& e){

	}
	catch(...){
		return false;
	}
	try{
		d->getAllCreaturesByLevel(0, creatures, numOfCreatures);
	}
	catch(Department::InvalidInputException& e){

	}
	catch(...){
		return false;
	}
	try{
		d->getAllCreaturesByLevel(666, NULL, numOfCreatures);
	}
	catch(Department::MagiIDNotFoundException& e){

	}
	catch(...){
		return false;
	}


	return true;
}

/*
 * Liron's notes to self:
 * - are we supposed to catch exceptions by reference or by address?
 * - add (magiID < 0) functionality to getMostDangerous
 * - find out how to implement the arrays in getMostDangerous
 * - I split the test up into functions because I won't be performing some right away
 * 		all test should be fine, other than replaceMagi and getAllCreatures
 */


int main(){


	// init test - passed - GREAT SUCCESS
	Department* d = new Department();


	bool flag = true;		// to be fair, this is pointless other than making me feel good about myself

	flag &= addMagizoologistTest(d);		// passed

	flag &= addCreatureTest(d);

	flag &= releaseCreatureTest(d);

	//flag &= replaceMagizoologistTest(d);		// TODO: This one is Tal's

	flag &= increaseLevelTest(d);

	flag &= getMostDangerousTest(d);

	//flag &= getAllCreaturesByLevelTest(d);		// TODO: add all creatures functionality


	// Quit test
	delete d;

	// gg wp ez

}
