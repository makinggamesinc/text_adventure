#include "stdio.h"
#include "stdbool.h"
#include "assert.h"

///////////////////////*********** Helper functions **************////////////////////
bool stringMatch(char *stringA, char *stringB) {
	bool result = true;

	// [q][u][i][t][\0]
	// [q][u][i][t][a][\0]

	while(*stringA != '\0' && *stringB != '\0') {
		result = (*stringB == *stringA);
			
		stringA += 1;
		stringB += 1;

		if(!result) {
			break;
		}
	}

	if(result) {
		result = (*stringA == '\0') && (*stringB == '\0');
	}

	return result;
}

void removeNewlineAtEnd(char *nullTerminatedString) {
	bool found = false;

	//NOTE(ollie): This function allows us to remove the newline character which fgets adds implicitly
	while(*nullTerminatedString != '\0' && !found) {
			if(nullTerminatedString[0] == '\n' && nullTerminatedString[1] == '\0') {
				nullTerminatedString[0] = '\0';
				found = true;
				break;
			}

			nullTerminatedString++;
	}
}
////////////////////////////////////////////////////////////////////

///////////////////////************ Game Types *************////////////////////

typedef enum {
	MONSTER = 0, 
	PERSON = 1,
	ITEM = 2,
} EntityType;

typedef struct {
	char *name;
	EntityType type;
} Entity;

typedef struct {
	char *name;
	char *description;

	int entityCount;
	Entity entities[256];
} Room;

////////////////////////////////////////////////////////////////////

#define MAX_RESPONSE_CHARS 256

// [h][e][y][\0]
// [h][e][y][\0][\0]

int main(char **args, int argc) {
		
	bool gameIsRunning = true; 

	Room room1 = {0};

	room1.name = "First room";
	room1.description = "A dark dank room";
	room1.entityCount = 0;

	Room *currentRoom = &room1;

	//NOTE(ollie): Game Loop
	while(gameIsRunning) {

		///////////////////////************ Print out current location *************////////////////////
		if(currentRoom) {
			printf("%s\n", currentRoom->name);
			printf("%s\n", currentRoom->description);

			for(int i = 0; i < currentRoom->entityCount; ++i) {

				Entity entity = currentRoom->entities[i];
				printf("%s\n", entity.name);

			}

		} else {
			printf("ERROR: no room assigned.\n");	
			assert(false);
		}

		////////////////////////////////////////////////////////////////////

		///////////////////////*********** Ask player for option**************////////////////////
		printf("%s\n", "What do you do?");

		char response[MAX_RESPONSE_CHARS];
		if(fgets(response, MAX_RESPONSE_CHARS, stdin) == 0) {
			printf("Something went wrong with fgets\n");	
			gameIsRunning = false;
		} else {
			removeNewlineAtEnd(response);


			printf("Your response was %s\n", response);

			////////////////////////////////////////////////////////////////////	

			//NOTE(ollie): Check for quit resposes
			if(response[0] == 'q' && response[1] == '\0') {
				gameIsRunning = false;
			} else if (stringMatch(response, "quit")) {
				gameIsRunning = false;
			}
			////////////////////////////////////////////////////////////////////

			///////////////////////************* Handle input resposes ************////////////////////
		}
	}
	

	return 0;
}