/****************************************************************************/
/*                                                                          */
/* This file contains the interface functions                               */
/* you should use for the wet ex 1                                          */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/*                                                                          */
/* File Name : library1.h                                                   */
/*                                                                          */
/****************************************************************************/

#ifndef _234218_WET1_
#define _234218_WET1_

#ifdef __cplusplus
extern "C" {
#endif

/* Return Values
 * ----------------------------------- */
typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusType;

/* Required Interface for the Data Structure
 * -----------------------------------------*/

/* Description:   Initiates the data structure.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: A pointer to a new instance of the data structure - as a void* pointer.
 */
void* Init();

/* Description:   Adds a new Magizoologist.
 * Input:         DS - A pointer to the data structure.
 *                magiID - The ID of the Magizoologist to add.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or if magiID <= 0.
 *                FAILURE - If magiID is already in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType AddMagizoologist(void *DS, int magiID);

/* Description:   Adds a new magical creature to the system.
 * Input:         DS - A pointer to the data structure.
 *                creatureID - ID of the creature to add.
 *                magiID - The ID of the magizoologist assigned to this creature
 *                level - The creature's initial danger level
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, or if creatureID <=0, or if magiID <=0, or if levelCount < 0
 *                FAILURE - If creatureID is already in the DS, or magiID isn't in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType AddCreature(void *DS, int creatureID, int magiID, int level);

/* Description:   Removes an existing creature.
 * Input:         DS - A pointer to the data structure.
 *                creatureID - The ID of the creature to remove.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or if creatureID <= 0.
 *                FAILURE - If creatureID isn't in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType ReleaseCreature(void *DS, int creatureID);

/* Description:   Removes an existing magizoologist, and transfers he's/she's creatures
 * 				  to a replacing magizoologist.
 * Input:         DS - A pointer to the data structure.
 *                MagiID - The ID of the magizoologist to remove.
 *                ReplacementID - The ID of the replacing magizoologist
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or if MagiID <= 0 or if ReplacementID <= 0 or MagiID==ReplacementID
 *                FAILURE - If creatureID isn't in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType ReplaceMagizoologist(void *DS, int MagiID, int ReplacementID);

/* Description:   Increases the danger level of a creature.
 * Input:         DS - A pointer to the data structure.
 *                creatureID - The ID of the creature.
 *		          LevelIncrease - The increase in the creature's level.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, or if creatureID<=0, or if levelIncrease<=0
 *                FAILURE - If creatureID isn't in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType IncreaseLevel(void *DS, int creatureID, int levelIncrease);

/* Description:   Returns the most dangerous creature assigned to magiID
 * 			      If magiID < 0, returns the most dangerous creature in the entire DS.
 * Input:         DS - A pointer to the data structure.
 *                magiID - The magizoologist that we would like to get the data for.
 * Output:        creatureID - A pointer to a variable that should be updated to the ID of the most dangerous creature.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, or if creatureID == NULL, or if magiID == 0.
 *                SUCCESS - Otherwise.
 */
StatusType GetMostDangerous(void *DS, int magiID, int *creatureID);

/* Description:   Returns all the creatures assigned to magiID sorted by their danger level.
 *           			If magiID < 0, returns all the creatures in the entire DS sorted by their danger level.
 * Input:         DS - A pointer to the data structure.
 *                magiID - The magizoologist that we'd like to get the data for.
 * Output:        creatures - A pointer to a to an array that you should update with the creatures' IDs sorted by their danger level,
 *			                  in case two creatures have same danger level they should be sorted by their ID.
 *                numOfCreatures - A pointer to a variable that should be updated to the number of returned creatures.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If any of the arguments is NULL or if magiID == 0.
 *                SUCCESS - Otherwise.
 */
StatusType GetAllCreaturesByLevel(void *DS, int magiID, int **creatures, int *numOfCreatures);

/* Description:   Quits and deletes the database.
 *                DS should be set to NULL.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: None.
 */
void Quit(void** DS);

#ifdef __cplusplus
}
#endif

#endif    /*_234218_WET1_ */
