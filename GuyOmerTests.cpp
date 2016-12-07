#include <iostream>
#include <cstdlib>
#include "RPtst.h"
#include "library1.h"

using namespace std;

#define DONT_CARE 999
#define VERY_BIG_NUMBER 255000
#define VERY_MEDIUM_NUMBER 100


//Research Tests
bool ResearchProjectInitQuitStressTest() {

	void* aLotOfResearches[VERY_BIG_NUMBER];
	for (int i = 0; i < VERY_BIG_NUMBER; i++) {
		aLotOfResearches[i] = Init();
	}
	for (int i = 0; i < VERY_BIG_NUMBER; i++) {
		Quit(&(aLotOfResearches[i]));
	}

	return true;
}

bool ResearchProjcectAddMagiTest() {
	void* r = Init();
	ASSERT_NOT_EQUALS(NULL, r);

	//Invalid Input
	ASSERT_EQUALS(INVALID_INPUT, AddMagizoologist(NULL, DONT_CARE));
	ASSERT_EQUALS(INVALID_INPUT, AddMagizoologist(r, -1));
	ASSERT_EQUALS(INVALID_INPUT, AddMagizoologist(r, 0));

	//Success
	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 1));
	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 2));
	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 3));

	//Failure
	ASSERT_EQUALS(FAILURE, AddMagizoologist(r, 1));

	Quit(&r);
	return true;
}

bool ResearchProjcectAddCreatureTest() {
	void* r = Init();
	ASSERT_NOT_EQUALS(NULL, r);

	//Invalid Input
	ASSERT_EQUALS(INVALID_INPUT, AddCreature(NULL, DONT_CARE, DONT_CARE, DONT_CARE));
	ASSERT_EQUALS(INVALID_INPUT, AddCreature(r, -1, DONT_CARE, DONT_CARE));
	ASSERT_EQUALS(INVALID_INPUT, AddCreature(r, 0, DONT_CARE, DONT_CARE));
	ASSERT_EQUALS(INVALID_INPUT, AddCreature(r, DONT_CARE, -1, DONT_CARE));
	ASSERT_EQUALS(INVALID_INPUT, AddCreature(r, DONT_CARE, 0, DONT_CARE));
	ASSERT_EQUALS(INVALID_INPUT, AddCreature(r, DONT_CARE, DONT_CARE, -1));
	ASSERT_EQUALS(INVALID_INPUT, AddCreature(r, 0, 0, -1));

	//Success
	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 1));
	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 2));
	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 3));

	ASSERT_EQUALS(SUCCESS, AddCreature(r, 100, 1, 323));
	ASSERT_EQUALS(SUCCESS, AddCreature(r, 200, 1, 131));
	ASSERT_EQUALS(SUCCESS, AddCreature(r, 300, 1, 323));

	//Stress test
	for (int i = 1; i < VERY_BIG_NUMBER / 1000; i++) {
		ASSERT_EQUALS(SUCCESS, AddCreature(r, 300 + 100 * i, 3, 101 * i));
	}

	//Failure
	ASSERT_EQUALS(FAILURE, AddCreature(r, 100, 1, DONT_CARE)); // Creature already exists for magi
	ASSERT_EQUALS(FAILURE, AddCreature(r, 100, 2, DONT_CARE)); // Creature already exists for another magi
	ASSERT_EQUALS(FAILURE, AddCreature(r, 400, 4, DONT_CARE)); // Magi does not exist

	Quit(&r);
	return true;
}

bool ResearchProjcectReleaseCreatureTest() {
	void* r = Init();
	ASSERT_NOT_EQUALS(NULL, r);

	//Invalid input check
	ASSERT_EQUALS(INVALID_INPUT, ReleaseCreature(NULL, DONT_CARE));
	ASSERT_EQUALS(INVALID_INPUT, ReleaseCreature(r, -1));
	ASSERT_EQUALS(INVALID_INPUT, ReleaseCreature(r, 0));

	//Success check
	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 1));
	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 2));

	ASSERT_EQUALS(SUCCESS, AddCreature(r, 100, 1, 323));
	ASSERT_EQUALS(SUCCESS, AddCreature(r, 200, 1, 131));
	ASSERT_EQUALS(SUCCESS, AddCreature(r, 300, 1, 323));

	ASSERT_EQUALS(SUCCESS, ReleaseCreature(r, 200));
	ASSERT_EQUALS(SUCCESS, ReleaseCreature(r, 100));
	ASSERT_EQUALS(SUCCESS, ReleaseCreature(r, 300));

	//Stress test
	for (int i = 1; i < VERY_BIG_NUMBER / 1000; i++) {
		ASSERT_EQUALS(SUCCESS, AddCreature(r, 300 + 100 * i, 2, 101 * i));
	}

	for (int i = 1; i < VERY_BIG_NUMBER / 1000; i++) {
		ASSERT_EQUALS(SUCCESS, ReleaseCreature(r, 300 + 100 * i));
	}

	//Failure check
	ASSERT_EQUALS(FAILURE, ReleaseCreature(r, 400)); // Creature does not exist in the research

	ASSERT_EQUALS(SUCCESS, AddCreature(r, 400, 1, 323));
	ASSERT_EQUALS(SUCCESS, ReleaseCreature(r, 400));
	ASSERT_EQUALS(FAILURE, ReleaseCreature(r, 400));

	Quit(&r);
	return true;
}

bool ResearchProjcectReplaceMagiTest() {
	void* r = Init();
	ASSERT_NOT_EQUALS(NULL, r);

	//Invalid input check
	ASSERT_EQUALS(INVALID_INPUT, ReplaceMagizoologist(NULL, DONT_CARE, DONT_CARE + 1));
	ASSERT_EQUALS(INVALID_INPUT, ReplaceMagizoologist(r, -1, DONT_CARE));
	ASSERT_EQUALS(INVALID_INPUT, ReplaceMagizoologist(r, 0, DONT_CARE));
	ASSERT_EQUALS(INVALID_INPUT, ReplaceMagizoologist(r, DONT_CARE, -1));
	ASSERT_EQUALS(INVALID_INPUT, ReplaceMagizoologist(r, DONT_CARE, 0));
	ASSERT_EQUALS(INVALID_INPUT, ReplaceMagizoologist(r, -1, -2));
	ASSERT_EQUALS(INVALID_INPUT, ReplaceMagizoologist(r, 0, -1));
	ASSERT_EQUALS(INVALID_INPUT, ReplaceMagizoologist(r, 1, 1)); // invalid because 1=1

	//Success check
	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 1));
	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 2));
	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 3));
	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 4));
	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 11));
	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 22));
	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 33));
	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 44));

	for (int i = 1; i < VERY_MEDIUM_NUMBER; i++) {
		if (i % 2 == 0) {
			ASSERT_EQUALS(SUCCESS, AddCreature(r, 100 * i, 2, 500 - i));
			ASSERT_EQUALS(SUCCESS, AddCreature(r, 100 * i + 1, 22, 500 - i));
		}
		else {
			ASSERT_EQUALS(SUCCESS, AddCreature(r, 100 * i, 4, 500 - i));
			ASSERT_EQUALS(SUCCESS, AddCreature(r, 100 * i + 1, 44, 500 - i));
		}
	}

	ASSERT_EQUALS(SUCCESS, ReplaceMagizoologist(r, 1, 3)); // magi 1 disappeared, magi 3 still knows nothing
	ASSERT_EQUALS(SUCCESS, ReplaceMagizoologist(r, 2, 33)); // magi 2 disappeared, magi 33 now has 49 creatures
	ASSERT_EQUALS(SUCCESS, ReplaceMagizoologist(r, 11, 4)); // magi 11 disappeared, magi 4 still has 49 creatures
	ASSERT_EQUALS(SUCCESS, ReplaceMagizoologist(r, 22, 44)); // magi 22 disappeared, magi 44 now has 100 creatures

	ASSERT_EQUALS(SUCCESS, AddCreature(r, 42, 3, DONT_CARE)); // magi 3 never disappeared in the first place
	ASSERT_EQUALS(SUCCESS, ReleaseCreature(r, 42)); // Get out !

	int* creatures;
	int numberOfCreatures;
	ASSERT_EQUALS(SUCCESS, GetAllCreaturesByLevel(r, 3, &creatures, &numberOfCreatures));

	ASSERT_EQUALS(0, numberOfCreatures); // magi 3 had 0 creatures. Magi 1 saw that magi 3 was sad, but he had no creatures to give him, so he disapparated, feeling ashamed
	free(creatures);

	ASSERT_EQUALS(SUCCESS, GetAllCreaturesByLevel(r, 33, &creatures, &numberOfCreatures));
	ASSERT_EQUALS(VERY_MEDIUM_NUMBER / 2 - 1, numberOfCreatures); // magi 33 had 0 creatures. Magi 2 saw that magi 33 was sad, so he decided to give him his creatures, and disapparated (very odd..)
	free(creatures);

	ASSERT_EQUALS(SUCCESS, GetAllCreaturesByLevel(r, 4, &creatures, &numberOfCreatures));
	ASSERT_EQUALS(VERY_MEDIUM_NUMBER / 2, numberOfCreatures); // magi 4 had 50 creatures. Magi 11 saw that magi 4 was proud, so he disapparated, feeling not helpful 
	free(creatures);

	ASSERT_EQUALS(SUCCESS, GetAllCreaturesByLevel(r, 44, &creatures, &numberOfCreatures));
	ASSERT_EQUALS(VERY_MEDIUM_NUMBER - 1, numberOfCreatures); // magi 44 had 49 creatures. Magi 22 saw that magi 44 was a brother, so he gave him his creatures, and disapparated (thx bro)
	free(creatures);

	//Failure check
	ASSERT_EQUALS(FAILURE, ReplaceMagizoologist(r, 5, 3)); // magi 5 was never invited to the research
	ASSERT_EQUALS(FAILURE, ReplaceMagizoologist(r, 3, 5)); // magi 5 was never invited to the research (again...)
	ASSERT_EQUALS(FAILURE, AddCreature(r, DONT_CARE, 1, DONT_CARE)); // magi 1 disappeared, so no creatures for him anymore

	Quit(&r);
	return true;
}

bool ResearchProjcectIncreaseLevelTest() {
	void* r = Init();
	ASSERT_NOT_EQUALS(NULL, r);

	//Invalid input check
	ASSERT_EQUALS(INVALID_INPUT, IncreaseLevel(NULL, DONT_CARE, DONT_CARE));
	ASSERT_EQUALS(INVALID_INPUT, IncreaseLevel(r, -1, DONT_CARE));
	ASSERT_EQUALS(INVALID_INPUT, IncreaseLevel(r, 0, DONT_CARE));
	ASSERT_EQUALS(INVALID_INPUT, IncreaseLevel(r, DONT_CARE, -1));
	ASSERT_EQUALS(INVALID_INPUT, IncreaseLevel(r, DONT_CARE, 0));
	ASSERT_EQUALS(INVALID_INPUT, IncreaseLevel(r, 0, 0));

	//Failure check
	ASSERT_EQUALS(FAILURE, IncreaseLevel(r, 100, DONT_CARE));

	//Success check
	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 1));

	for (int i = 0; i < 10; i++) {
		ASSERT_EQUALS(SUCCESS, AddCreature(r, 100 + i * 100, 1, 101 + i * 100));
	}
	int mostDangerousID;
	ASSERT_EQUALS(SUCCESS, GetMostDangerous(r, 1, &mostDangerousID));
	ASSERT_EQUALS(1000, mostDangerousID); // 1000 is the ID of the most dangerous creature
	ASSERT_EQUALS(SUCCESS, IncreaseLevel(r, 200, 1000)); // level before = 201, level after = 1201
	ASSERT_EQUALS(SUCCESS, GetMostDangerous(r, 1, &mostDangerousID));
	ASSERT_EQUALS(200, mostDangerousID); // because it's level was updated to 1201 (the highest) two lines above
	ASSERT_EQUALS(SUCCESS, IncreaseLevel(r, 100, 600)); // level before = 101, level after = 701
	ASSERT_EQUALS(SUCCESS, GetMostDangerous(r, 1, &mostDangerousID));
	ASSERT_EQUALS(200, mostDangerousID); // nothing was changed
	ASSERT_EQUALS(SUCCESS, IncreaseLevel(r, 100, 600)); // level before = 701, level after = 1301
	ASSERT_EQUALS(SUCCESS, GetMostDangerous(r, 1, &mostDangerousID));
	ASSERT_EQUALS(100, mostDangerousID); // because it's level was updated to 1301 (the highest) two lines above
	Quit(&r);
	return true;
}

bool ResearchProjcectGetMostDangerousTest() {
	void* r = Init();
	ASSERT_NOT_EQUALS(NULL, r);

	int creatureID;
	//Invalid input check
	ASSERT_EQUALS(INVALID_INPUT, GetMostDangerous(NULL, DONT_CARE, &creatureID));
	ASSERT_EQUALS(INVALID_INPUT, GetMostDangerous(r, DONT_CARE, NULL));
	ASSERT_EQUALS(INVALID_INPUT, GetMostDangerous(r, 0, &creatureID));
	ASSERT_EQUALS(INVALID_INPUT, GetMostDangerous(r, 0, NULL));


	//Success check
	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 1));
	ASSERT_EQUALS(SUCCESS, GetMostDangerous(r, 1, &creatureID));
	ASSERT_EQUALS(-1, creatureID); // no creatures were added to magi 1
	ASSERT_EQUALS(SUCCESS, GetMostDangerous(r, -50, &creatureID));
	ASSERT_EQUALS(-1, creatureID); // no creatures were added

	for (int i = 0; i < 10; i++) {
		ASSERT_EQUALS(SUCCESS, AddCreature(r, 100 + i * 100, 1, 101 + i * 100)); // most dangerous is 1001
	}

	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 2));
	for (int i = 0; i < 5; i++) {
		ASSERT_EQUALS(SUCCESS, AddCreature(r, 50 + i * 100, 2, 51 + i * 100)); // most dangerous is 451
	}

	ASSERT_EQUALS(SUCCESS, GetMostDangerous(r, 1, &creatureID));
	ASSERT_EQUALS(1000, creatureID);
	ASSERT_EQUALS(SUCCESS, GetMostDangerous(r, 2, &creatureID));
	ASSERT_EQUALS(450, creatureID);

	ASSERT_EQUALS(SUCCESS, GetMostDangerous(r, -50, &creatureID));
	ASSERT_EQUALS(1000, creatureID); // most dangerous across all the magis

	ASSERT_EQUALS(SUCCESS, ReleaseCreature(r, 1000)); // releasing the most dangerous creature (level = 1001)
	ASSERT_EQUALS(SUCCESS, GetMostDangerous(r, 1, &creatureID));
	ASSERT_EQUALS(900, creatureID);
	ASSERT_EQUALS(SUCCESS, GetMostDangerous(r, -50, &creatureID));
	ASSERT_EQUALS(900, creatureID); // most dangerous across all the magis

	ASSERT_EQUALS(SUCCESS, ReleaseCreature(r, 100)); // releasing least dangerous creature (level = 101)
	ASSERT_EQUALS(SUCCESS, GetMostDangerous(r, 1, &creatureID));
	ASSERT_EQUALS(900, creatureID); // did not changed
	ASSERT_EQUALS(SUCCESS, GetMostDangerous(r, -50, &creatureID));
	ASSERT_EQUALS(900, creatureID); // did not changed

	for (int i = 0; i < 5; i++) {
		ASSERT_EQUALS(SUCCESS, ReleaseCreature(r, 50 + i * 100)); // releasing the creatures of magi 2
	}

	ASSERT_EQUALS(SUCCESS, GetMostDangerous(r, 2, &creatureID));
	ASSERT_EQUALS(-1, creatureID); // no creatures were left for magi 2
	ASSERT_EQUALS(SUCCESS, GetMostDangerous(r, -50, &creatureID));
	ASSERT_EQUALS(900, creatureID); // did not changed

	for (int i = 1; i < 9; i++) {
		ASSERT_EQUALS(SUCCESS, ReleaseCreature(r, 100 + i * 100)); // releasing all the remaining creatures of magi 1
	}

	ASSERT_EQUALS(SUCCESS, GetMostDangerous(r, 1, &creatureID));
	ASSERT_EQUALS(-1, creatureID); // no creatures were left for magi 1
	ASSERT_EQUALS(SUCCESS, GetMostDangerous(r, -50, &creatureID));
	ASSERT_EQUALS(-1, creatureID);// no creatures were left at all


	//Failure Check
	ASSERT_EQUALS(FAILURE, GetMostDangerous(r, 9, &creatureID)); // no magi with this id
	Quit(&r);
	return true;
}

bool ResearchProjcectGetAllCreaturesByLevelTest() {
	void* r = Init();
	ASSERT_NOT_EQUALS(NULL, r);

	int* creaturesLevel;
	int numberOfCreatures;
	//Invalid input check
	ASSERT_EQUALS(INVALID_INPUT, GetAllCreaturesByLevel(NULL, DONT_CARE, &creaturesLevel, &numberOfCreatures));
	ASSERT_EQUALS(INVALID_INPUT, GetAllCreaturesByLevel(r, 0, &creaturesLevel, &numberOfCreatures));
	ASSERT_EQUALS(INVALID_INPUT, GetAllCreaturesByLevel(r, DONT_CARE, NULL, &numberOfCreatures));
	ASSERT_EQUALS(INVALID_INPUT, GetAllCreaturesByLevel(r, DONT_CARE, &creaturesLevel, NULL));
	ASSERT_EQUALS(INVALID_INPUT, GetAllCreaturesByLevel(r, 0, NULL, NULL));

	//Success check
	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 1));
	ASSERT_EQUALS(SUCCESS, GetAllCreaturesByLevel(r, 1, &creaturesLevel, &numberOfCreatures));
	ASSERT_EQUALS(0, numberOfCreatures); // no creatures were added
	ASSERT_EQUALS(NULL, creaturesLevel); // no creatures were added
	ASSERT_EQUALS(SUCCESS, GetAllCreaturesByLevel(r, -1, &creaturesLevel, &numberOfCreatures));
	ASSERT_EQUALS(0, numberOfCreatures); // no creatures were added
	ASSERT_EQUALS(NULL, creaturesLevel); // no creatures were added


	for (int i = 0; i < 10; i++) {
		ASSERT_EQUALS(SUCCESS, AddCreature(r, 100 + i * 100, 1, 101 + i * 100)); // most dangerous is 1001
	}

	ASSERT_EQUALS(SUCCESS, AddMagizoologist(r, 2));

	for (int i = 0; i < 5; i++) {
		ASSERT_EQUALS(SUCCESS, AddCreature(r, 50 + i * 100, 2, 51 + i * 100)); // most dangerous is 451
	}

	ASSERT_EQUALS(SUCCESS, GetAllCreaturesByLevel(r, 1, &creaturesLevel, &numberOfCreatures));
	ASSERT_EQUALS(10, numberOfCreatures); // 10 creatures were added to magi 1
	for (int i = 0; i < numberOfCreatures; i++) {
		ASSERT_EQUALS(creaturesLevel[i], 1000 - i * 100); // no creatures were added
	}
	free(creaturesLevel);

	ASSERT_EQUALS(SUCCESS, AddCreature(r, 1100, 1, 101)); // this creature has the same level as the creature with id 100
	ASSERT_EQUALS(SUCCESS, GetAllCreaturesByLevel(r, 1, &creaturesLevel, &numberOfCreatures));
	ASSERT_EQUALS(11, numberOfCreatures); // 11 creatures were added to magi 1
	ASSERT_EQUALS(creaturesLevel[9], 100); // 100 < 1100 so it should appear to the left of 1100
	ASSERT_EQUALS(creaturesLevel[10], 1100);
	free(creaturesLevel);
	ASSERT_EQUALS(SUCCESS, ReleaseCreature(r, 1100));

	ASSERT_EQUALS(SUCCESS, GetAllCreaturesByLevel(r, -333, &creaturesLevel, &numberOfCreatures));
	ASSERT_EQUALS(15, numberOfCreatures); // 15 creatures were added to the system
	for (int i = 0; i < 10; i++) {
		ASSERT_EQUALS(creaturesLevel[numberOfCreatures - i - 1], 50 + i * 50);
	}
	for (int i = 0; i < 5; i++) {
		ASSERT_EQUALS(creaturesLevel[i], 1000 - i*100);
	}
	free(creaturesLevel);

	Quit(&r);
	return true;
}

bool researchProjectTest() {
	RUN_TEST(ResearchProjectInitQuitStressTest);
	RUN_TEST(ResearchProjcectAddMagiTest);
	RUN_TEST(ResearchProjcectAddCreatureTest);
	RUN_TEST(ResearchProjcectReleaseCreatureTest);
	RUN_TEST(ResearchProjcectReplaceMagiTest);
	RUN_TEST(ResearchProjcectIncreaseLevelTest);
	RUN_TEST(ResearchProjcectGetMostDangerousTest);
	RUN_TEST(ResearchProjcectGetAllCreaturesByLevelTest);

	return true;
}

int main17() {
	researchProjectTest();
	// getchar();
	return 0;
}
