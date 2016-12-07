/***************************************************************************/
/*                                                                         */
/* 234218 Data DSs 1, Winter 2016-2017                                     */
/* Homework : Wet 1                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main1.cpp                                                   */
/*                                                                         */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library1.h"
#include <iostream>
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

/* The command's strings */
typedef enum {
	NONE_CMD = -2,
	COMMENT_CMD = -1,
	INIT_CMD = 0,
	ADDMAGI_CMD = 1,
	ADDCREATURE_CMD = 2,
	RELEASECREATURE_CMD = 3,
	REPLACEMAGI_CMD = 4,
	INCREASELEVEL_CMD = 5,
	GETMOSTDANGEROUS_CMD = 6,
	GETALLCREATURES_CMD = 7,
	QUIT_CMD = 8
} commandType;

static const int numActions = 9;
static const char *commandStr[] = {
		"Init",
		"AddMagizoologist",
		"AddCreature",
		"ReleaseCreature",
		"ReplaceMagizoologist",
		"IncreaseLevel",
		"GetMostDangerous",
		"GetAllCreaturesByLevel",
		"Quit" };

static const char* ReturnValToStr(int val) {
	switch (val) {
	case SUCCESS:
		return "SUCCESS";
	case ALLOCATION_ERROR:
		return "ALLOCATION_ERROR";
	case FAILURE:
		return "FAILURE";
	case INVALID_INPUT:
		return "INVALID_INPUT";
	default:
		return "";
	}
}

/* we assume maximum string size is not longer than 256  */
#define MAX_STRING_INPUT_SIZE (255)
#define MAX_BUFFER_SIZE       (255)

#define StrCmp(Src1,Src2) ( strncmp((Src1),(Src2),strlen(Src1)) == 0 )

typedef enum {
	error_free, error
} errorType;
static errorType parser(const char* const command);

#define ValidateRead(read_parameters,required_parameters,ErrorString) \
if ( (read_parameters)!=(required_parameters) ) { printf(ErrorString); return error; }

static bool isInit = false;

/***************************************************************************/
/* main                                                                    */
/***************************************************************************/

int main(int argc, const char**argv) {
	char buffer[MAX_STRING_INPUT_SIZE];

	// Reading commands
	while (fgets(buffer, MAX_STRING_INPUT_SIZE, stdin) != NULL) {
		fflush(stdout);
		if (parser(buffer) == error)
			break;
	};
	return 0;
}

/***************************************************************************/
/* Command Checker                                                         */
/***************************************************************************/

static commandType CheckCommand(const char* const command,
		const char** const command_arg) {
	if (command == NULL || strlen(command) == 0 || StrCmp("\n", command))
		return (NONE_CMD);
	if (StrCmp("#", command)) {
		if (strlen(command) > 1)
			printf("%s", command);
		return (COMMENT_CMD);
	};
	for (int index = 0; index < numActions; index++) {
		if (StrCmp(commandStr[index], command)) {
			*command_arg = command + strlen(commandStr[index]) + 1;
			return ((commandType) index);
		};
	};
	return (NONE_CMD);
}

/***************************************************************************/
/* Commands Functions                                                      */
/***************************************************************************/

static errorType OnInit(void** DS, const char* const command);
static errorType OnAddMagizoologist(void* DS, const char* const command);
static errorType OnAddCreature(void* DS, const char* const command);
static errorType OnReleaseCreature(void* DS, const char* const command);
static errorType OnReplaceMagizoologist(void* DS, const char* const command);
static errorType OnIncreaseLevel(void* DS, const char* const command);
static errorType OnGetMostDangerous(void* DS, const char* const command);
static errorType OnGetAllCreaturesByLevel(void* DS, const char* const command);
static errorType OnQuit(void** DS, const char* const command);

/***************************************************************************/
/* Parser                                                                  */
/***************************************************************************/

static errorType parser(const char* const command) {
	static void *DS = NULL; /* The general data structure */
	const char* command_args = NULL;
	errorType rtn_val = error;

	commandType command_val = CheckCommand(command, &command_args);

	switch (command_val) {

	case (INIT_CMD):
		rtn_val = OnInit(&DS, command_args);
		break;
	case (ADDMAGI_CMD):
		rtn_val = OnAddMagizoologist(DS, command_args);
		break;
	case (ADDCREATURE_CMD):
		rtn_val = OnAddCreature(DS, command_args);
		break;
	case (RELEASECREATURE_CMD):
		rtn_val = OnReleaseCreature(DS, command_args);
		break;
	case (REPLACEMAGI_CMD):
		rtn_val = OnReplaceMagizoologist(DS, command_args);
		break;
	case (INCREASELEVEL_CMD):
		rtn_val = OnIncreaseLevel(DS, command_args);
		break;
	case (GETMOSTDANGEROUS_CMD):
		rtn_val = OnGetMostDangerous(DS, command_args);
		break;
	case (GETALLCREATURES_CMD):
		rtn_val = OnGetAllCreaturesByLevel(DS, command_args);
		break;
	case (QUIT_CMD):
		rtn_val = OnQuit(&DS, command_args);
		break;

	case (COMMENT_CMD):
		rtn_val = error_free;
		break;
	case (NONE_CMD):
		rtn_val = error;
		break;
	default:
		assert(false);
		break;
	};
	return (rtn_val);
}

/***************************************************************************/
/* OnInit                                                                  */
/***************************************************************************/
static errorType OnInit(void** DS, const char* const command) {
	if (isInit) {
		printf("Init was already called.\n");
		return (error_free);
	};
	isInit = true;

	*DS = Init();
	if (*DS == NULL) {
		printf("Init failed.\n");
		return error;
	};
	printf("Init done.\n");

	return error_free;
}

/***************************************************************************/
/* OnAddMagizoologist                                                             */
/***************************************************************************/
static errorType OnAddMagizoologist(void* DS, const char* const command) {
	int magiID;
	ValidateRead(sscanf(command, "%d", &magiID), 1, "AddMagizoologist failed.\n");
	StatusType res = AddMagizoologist(DS, magiID);

	if (res != SUCCESS) {
		printf("AddMagizoologist: %s\n", ReturnValToStr(res));
		return error_free;
	} else {
		printf("AddMagizoologist: %s\n", ReturnValToStr(res));
	}

	return error_free;
}

/***************************************************************************/
/* OnAddCreature                                                          */
/***************************************************************************/
static errorType OnAddCreature(void* DS, const char* const command) {
	int creatureID;
	int magiID;
	int level;
	ValidateRead(
			sscanf(command, "%d %d %d", &creatureID, &magiID, &level),
			3, "AddCreature failed.\n");
	StatusType res = AddCreature(DS, creatureID, magiID, level);

	if (res != SUCCESS) {
		printf("AddCreature: %s\n", ReturnValToStr(res));
		return error_free;
	}

	printf("AddCreature: %s\n", ReturnValToStr(res));
	return error_free;
}

/***************************************************************************/
/* OnReleaseCreature                                                            */
/***************************************************************************/
static errorType OnReleaseCreature(void* DS, const char* const command) {
	int creatureID;
	ValidateRead(sscanf(command, "%d", &creatureID), 1,
			"ReleaseCreature failed.\n");
	StatusType res = ReleaseCreature(DS, creatureID);
	if (res != SUCCESS) {
		printf("ReleaseCreature: %s\n", ReturnValToStr(res));
		return error_free;
	}

	printf("ReleaseCreature: %s\n", ReturnValToStr(res));
	return error_free;
}

/***************************************************************************/
/* OnReleaseMagizoologist                                                            */
/***************************************************************************/
static errorType OnReplaceMagizoologist(void* DS, const char* const command) {
	int magiID;
	int replacementID;
	ValidateRead(sscanf(command, "%d %d", &magiID, &replacementID), 2,
			"ReplaceMagizoologist failed.\n");
	StatusType res = ReplaceMagizoologist(DS, magiID, replacementID);

	if (res != SUCCESS) {
		printf("ReplaceMagizoologist: %s\n", ReturnValToStr(res));
		return error_free;
	}

	printf("ReplaceMagizoologist: %s\n", ReturnValToStr(res));
	return error_free;
}

/***************************************************************************/
/* OnIncreaseLevel                                                         */
/***************************************************************************/
static errorType OnIncreaseLevel(void* DS, const char* const command) {
	int creatureID;
	int levelIncrease;
	ValidateRead(sscanf(command, "%d %d", &creatureID, &levelIncrease), 2,
			"IncreaseLevel failed.\n");
	StatusType res = IncreaseLevel(DS, creatureID, levelIncrease);

	if (res != SUCCESS) {
		printf("IncreaseLevel: %s\n", ReturnValToStr(res));
		return error_free;
	}

	printf("IncreaseLevel: %s\n", ReturnValToStr(res));
	return error_free;
}


/***************************************************************************/
/* OnGetMostDangerous                                                         */
/***************************************************************************/
static errorType OnGetMostDangerous(void* DS, const char* const command) {
	int magiID;
	ValidateRead(sscanf(command, "%d", &magiID), 1, "GetMostDangerous failed.\n");
	int creatureID;
	StatusType res = GetMostDangerous(DS, magiID, &creatureID);

	if (res != SUCCESS) {
		printf("GetMostDangerous: %s\n", ReturnValToStr(res));
		return error_free;
	}

	cout << "Most dangerous creature is: " << creatureID << endl;
	return error_free;
}

/***************************************************************************/
/* PrintAll                                                        */
/***************************************************************************/

void PrintAll(int *creatureIDs, int numOfCreatures) {
	if (numOfCreatures > 0) {
		cout << "Rank	||	Creature" << endl;
	}

	for (int i = 0; i < numOfCreatures; i++) {
		cout << i + 1 << "\t||\t" << creatureIDs[i] << endl;
	}
	cout << "and there are no more creatures!" << endl;

	free (creatureIDs);
}

static errorType OnGetAllCreaturesByLevel(void* DS, const char* const command) {
	int magiID;
	ValidateRead(sscanf(command, "%d", &magiID), 1,
			"GetAllCreaturesByLevel failed.\n");
	int* creatureIDs;
	int numOfCreatures;
	StatusType res = GetAllCreaturesByLevel(DS, magiID, &creatureIDs, &numOfCreatures);

	if (res != SUCCESS) {
		printf("GetAllCreaturesByLevel: %s\n", ReturnValToStr(res));
		return error_free;
	}

	PrintAll(creatureIDs, numOfCreatures);
	return error_free;
}

/***************************************************************************/
/* OnQuit                                                                  */
/***************************************************************************/
static errorType OnQuit(void** DS, const char* const command) {
	Quit(DS);
	if (*DS != NULL) {
		printf("Quit failed.\n");
		return error;
	};

	isInit = false;
	printf("Quit done.\n");

	return error_free;
}

#ifdef __cplusplus
}
#endif
