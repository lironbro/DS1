/*
 * test_BinTree.cpp
 *
 *  Created on: 27 ֳ¡ֳ°ֳ¥ֳ¡ֳ— 2016
 *      Author: Liron
 */

#include "Department.h"
#include "stdio.h"

bool addMagizoologistTest(Department* d){

	bool flag = false;

	// addMagizoologist test
	d->addMagizoologist(55);
	d->addMagizoologist(32);
	d->addMagizoologist(123);		// this guy should be empty the entire test

	try{
		d->addMagizoologist(32);
	}
	catch(Department::MagiIDAlreadyExistsException& e){
		flag = true;
	}
	catch(...){
		return false;
	}
	if(!flag)
		return flag;
	flag = false;

	try{
		d->addMagizoologist(-1);
	}
	catch(Department::InvalidInputException& e){
		flag = true;
	}
	catch(...){
		return false;
	}
	if(!flag)
		return flag;

	return true;
}


bool addCreatureTest(Department* d){

	bool flag = false;

	// addCreature test
	d->addCreature(5,55,8);		// should be initial most dangerous

	try{
		d->addCreature(5,55,9);		// should throw id already exists exception
	}
	catch(Department::CreatureIDAlreadyExistsException& e){
		flag = true;
	}
	catch(...){
		return false;
	}
	if(!flag)
		return flag;
	flag = false;

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
	catch(Department::CreatureIDAlreadyExistsException& e){
		flag = true;
	}
	catch(...){
		return false;
	}
	if(!flag)
		return flag;
	flag = false;

	try{
		d->addCreature(1001, 666, 1);
	}
	catch(Department::MagiIDNotFoundException& e){
		flag = true;
	}
	catch(...){
		return false;
	}
	if(!flag)
		return flag;
	flag = false;

	try{
		d->addCreature(-1000, 32, 1);		// negative creatureid
	}
	catch(Department::InvalidInputException& e){
		flag = true;
	}
	catch(...){
		return false;
	}
	if(!flag)
		return flag;
	flag = false;

	try{
		d->addCreature(1000, -32, 1);		// negative magiid
	}
	catch(Department::InvalidInputException& e){
		flag = true;
	}
	catch(...){
		return false;
	}
	if(!flag)
		return flag;
	flag = false;

	try{
		d->addCreature(1000, 32, -1);		// nonpositive level
	}
	catch(Department::InvalidInputException& e){
		flag = true;
	}
	catch(...){
		return false;
	}
	if(!flag)
		return flag;




	return true;
}


bool releaseCreatureTest(Department* d){

	bool flag = false;

	// releaseCreature test
	d->releaseCreature(5);			// should remove this one, most dangerous in 55 magi
	try{
		d->releaseCreature(5);
	}
	catch(Department::CreatureIDNotFoundException& e){

		flag = true;
	}
	catch(...){
		return false;
	}
	if(!flag)
		return flag;
	flag = false;

	try{
		d->releaseCreature(1337);
	}
	catch(Department::CreatureIDNotFoundException& e){
		flag = true;
	}
	catch(...){
		return false;
	}
	if(!flag)
		return flag;
	flag = false;

	try{
		d->releaseCreature(-10);			// negative id
	}
	catch(Department::InvalidInputException& e){
		flag = true;
	}
	catch(...){
		return false;
	}
	if(!flag)
		return flag;
	flag = false;

	return true;
}


bool replaceMagizoologistTest(Department* d){		//TODO: finish this ship

	// ReplaceMagizoologist test

	Magizoologist* magi;
	AVLTree<Creature, int>* byId;
	AVLTree<Creature, levelKey>* byLevel;

	d->addMagizoologist(80);
	d->addCreature(800, 80, 10);
	d->addCreature(801, 80, 11);
	magi = d->getMagi(80);
	byId = magi->getCreaturesById();
	byLevel = magi->getCreaturesByLevel();
	// 80 will contain 800 (root), and 801 (right) (both by index and level)

	d->addMagizoologist(81);
	d->addCreature(810, 81, 10);
	d->addCreature(811, 81, 20);
	d->addCreature(812, 81, 5);
	magi = d->getMagi(81);
	byId = magi->getCreaturesById();
	byLevel = magi->getCreaturesByLevel();
	// 81 will contain 810 (root), 811 (right), and 812 (left) (by level)
	// by index its 811 (root), 810(left), 812 (right)

	d->addMagizoologist(82);
	magi = d->getMagi(82);
	byId = magi->getCreaturesById();
	byLevel = magi->getCreaturesByLevel();
	// 82 will be empty

	d->addMagizoologist(83);
	magi = d->getMagi(83);
	byId = magi->getCreaturesById();
	byLevel = magi->getCreaturesByLevel();
	// 83 will be empty

	d->replaceMagizoologist(80, 81);
	magi = d->getMagi(81);
	byId = magi->getCreaturesById();
	byLevel = magi->getCreaturesByLevel();
	magi = d->getMagi(80);
	byId = magi->getCreaturesById();
	byLevel = magi->getCreaturesByLevel();
	// by level:
	// 								10, 810 root
	//			10, 800 left						20, 811 right
	// 	5, 812 left			11, 801 right
	//
	// by index:
	//								811 root
	//			801 left							812 right
	//	800 left			810 right
	d->replaceMagizoologist(82, 83);
	magi = d->getMagi(83);
	// should be empty
	d->replaceMagizoologist(81, 83);
	// by level:
	// 								10, 810 root
	//			10, 800 left						20, 811 right
	// 	5, 812 left			11, 801 right
	//
	// by index:
	//								811 root
	//			801 left							812 right
	//	800 left			810 right

	d->replaceMagizoologist(83, 123);
	magi = d->getMagi(123);
	byId = magi->getCreaturesById();
	byLevel = magi->getCreaturesByLevel();
	// by level:
	// 								10, 810 root
	//			10, 800 left						20, 811 right
	// 	5, 812 left			11, 801 right
	//
	// by index:
	//								811 root
	//			801 left							812 right
	//	800 left			810 right


	d->releaseCreature(800);
	// by level:
	// 								10, 810 root
	//			11, 801 left						20, 811 right
	// 	5, 812 left
	//
	// by index:
	//								811 root
	//			801 left							812 right
	//					810 right
	d->releaseCreature(801);
	// by level:
	// 								10, 810 root
	//			5, 812 left						20, 811 right
	//
	// by index:
	//								811 root
	//			810 left							812 right

	d->releaseCreature(810);
	// by level:
	// 								20, 811 root
	//			5, 812 left
	//
	// by index:
	//								811 root
	//											812 right
	d->releaseCreature(811);
	// by level:
	// 								20, 812 root
	//
	// by index:
	//								812 root
	d->releaseCreature(812);
	// empty

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

	bool flag = false;

	// getMostDangerous test
	int* dangerous = (int*)malloc(sizeof(*dangerous));		//TODO: is malloc good for this?
	d->getMostDangerous(32, dangerous);		// dangerous should point to 500 (or 502 if increase lvl fails)
	d->getMostDangerous(55, dangerous);		// dangerous should point to 2 (or 5 if increase fails)
	d->getMostDangerous(123, dangerous);	// dangerous should point to be -1
	d->getMostDangerous(-1000, dangerous);	// dangerous should point to 500 (or 502 if increase fails)
	try{
		d->getMostDangerous(666, dangerous);		// no magi id

	}
	catch(Department::MagiIDNotFoundException& e){
		flag = true;
	}
	catch(...){
		return false;
	}
	if(!flag)
		return flag;
	flag = false;

	try{
		d->getMostDangerous(0, dangerous);		// negative id
	}
	catch(Department::InvalidInputException& e){
		flag = true;
	}
	catch(...){
		return false;
	}
	if(!flag)
		return flag;
	flag = false;

	try{
		d->getMostDangerous(123, NULL);		// null pointer

	}
	catch(Department::InvalidInputException& e){
		flag = true;
	}
	catch(...){
		return false;
	}
	if(!flag)
		return flag;
	flag = false;

	return true;
}



bool getAllCreaturesByLevelTest(Department* d){

	bool flag = false;

	// getAllCreaturesByLevel test
	int res;
	int* numOfCreatures = &res;
	int* arr;
	int** creatures = &arr;		// TODO: is this the way to do this? I think creatures could be NULL
	d->getAllCreaturesByLevel(-1, creatures, numOfCreatures); 	// should return all creatures
	free(*creatures);		// this causes problems
	d->getAllCreaturesByLevel(32, creatures, numOfCreatures);
	free(*creatures);
	d->getAllCreaturesByLevel(123, creatures, numOfCreatures);		// creatures should be NULL, num should be 0
	free(*creatures);
	try{
		d->getAllCreaturesByLevel(123, NULL, numOfCreatures);
	}
	catch(Department::InvalidInputException& e){
		flag = true;
	}
	catch(...){
		return false;
	}
	if(!flag)
		return flag;
	flag = false;

	try{
		d->getAllCreaturesByLevel(123, creatures, NULL);
	}
	catch(Department::InvalidInputException& e){
		flag = true;
	}
	catch(...){
		return false;
	}
	if(!flag)
		return flag;
	flag = false;

	try{
		d->getAllCreaturesByLevel(0, creatures, numOfCreatures);
	}
	catch(Department::InvalidInputException& e){
		flag = true;
	}
	catch(...){
		return false;
	}
	if(!flag)
		return flag;
	flag = false;

	try{
		d->getAllCreaturesByLevel(666, creatures, numOfCreatures);
	}
	catch(Department::MagiIDNotFoundException& e){
		flag = true;
	}
	catch(...){
		return false;
	}
	if(!flag)
		return flag;
	flag = false;


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



	if(flag){
		printf("starting tests\n");
	}
	flag &= addMagizoologistTest(d);		// passed
	if(flag)
		printf("passed addMagizoologistTest\n");
	else
		printf("failed addMagizoologistTest\n");

	flag &= addCreatureTest(d);
	if(flag)
		printf("passed addCreatureTest\n");
	else
		printf("failed addCreatureTest\n");

	flag &= releaseCreatureTest(d);
	if(flag)
		printf("passed releaseCreatureTest\n");
	else
		printf("failed releaseCreatureTest\n");



	flag &= replaceMagizoologistTest(d);		// TODO: This one is Tal's
	if(flag)
		printf("passed replaceMagizoologistTest\n");
	else
		printf("failed replaceMagizoologistTest\n");



	flag &= increaseLevelTest(d);
	if(flag)
		printf("passed increaseLevelTest\n");
	else
		printf("failed increaseLevelTest\n");



	flag &= getMostDangerousTest(d);
	if(flag)
		printf("passed getMostDangerousTest\n");
	else
		printf("failed getMostDangerousTest\n");



	flag &= getAllCreaturesByLevelTest(d);		// TODO: add all creatures functionality
	if(flag)
		printf("passed getAllCreaturesByLevelTest\n");
	else
		printf("failed getAllCreaturesByLevelTest\n");


	// Quit test
	delete d;


	if(flag == true)
		printf("looks like this works :) \n");
	else
		printf("doesn't work :( \n");

	// gg wp ez

}
