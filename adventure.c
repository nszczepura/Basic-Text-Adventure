#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "items.h"
#include "rooms.h"

static char command[100];
struct Item *playerInventory;
int checkWin = 0;

//player input
static int get_command() {

	printf(">");
	fgets(command, sizeof(command), stdin);
	printf("\n");
	return (command != NULL);

}

//prints a list of commands and their functions
void print_help() {

	printf("Available commands are look, go, take, drop, inventory, and quit\n\n");
	printf("Use look for details on your location\n\n");
	printf("Use go DIRECTION to move. available directions are\n");
	printf("north, south, west, east. For example go north\n\n");
	printf("Use take to pick up items in a room.\n");
	printf("for example if there is an item redkey, take redkey.\n\n");
	printf("drop functions similarly to take.\n\n");
	printf("Use inventory to display your current items\n\n");

}

//splits up player input to action and object then executes a function
//based on those parameters
static int execute_command(struct Room **currentRoom) {

	char *action = strtok(command, " \n");
	char *object = strtok(NULL, " \n");
	
	if(command != NULL){
		
		if(strcmp(action, "quit") == 0) { 
			return 0; 
		}
		
		else if(strcmp(action, "look") == 0) { 
			look_room(*currentRoom); 
		}
		
		else if(strcmp(action, "go") == 0) { 
			*currentRoom = go_room(*currentRoom, object); 
		}

		else if(strcmp(action, "use") == 0) {
			checkWin = use_key(currentRoom, object);
		}

		else if(strcmp(action, "take") == 0) {
			
			struct Item *current_items = room_items(*currentRoom);
			struct Item *pickup = item_take(&current_items, object);
			
			if(pickup == NULL) {
				printf("I couldn't find that item\n");
			}

			else{

				if(playerInventory == NULL) {
					playerInventory = item(item_name(pickup), item_description(pickup), NULL);
				}

				else {
					pickup->next = playerInventory;
					playerInventory = pickup;
				}

			}

		}
		
		else if(strcmp(action, "inventory") == 0) {
			printf("I'm holding: \n");
			print_items(playerInventory);
		}

		else if(strcmp(action, "drop") == 0) {
			struct Item *drop = item_take(&playerInventory, object);
			free(drop);
		}

		else if(strcmp(action, "help") == 0) {
			print_help(); 
	  }
		
		else { 
			printf("I'm afraid I cannot do that\n"); 
			printf("(need help?, enter help for a list of commands)\n");
		}

	}

	return 1;

}

int main(){

//initialize games
	struct Room *currentRoom = initial_rooms();
	playerInventory = NULL;

	printf("No one is coming to rescue us\n");
	printf("I have to get off this ship\n");
	printf("There are some escape pods but I need the\n"); 
	printf("podkey to activate one of the escape pods\n");
	printf("What should I do next?\n");

	while(get_command() && execute_command(&currentRoom) && !checkWin);
	
	if(checkWin == 1) {
		printf("Congratulations! You escaped!\n\n");
	}

	printf("\nThanks for Playing!\n");

	return 0;
}
