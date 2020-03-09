#include "stdio.h"
#include "stdbool.h"

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

int main(char **args, int argc) {
		
	bool gameIsRunning = true; 

	//NOTE(ollie): Game Loop
	while(gameIsRunning) {
		///////////////////////*********** Ask player for option**************////////////////////
		printf("%s\n", "What do you do?");

		char response[2];
		scanf("%s", response);
			
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
	

	return 0;
}