#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rooms.h"
#include "items.h"

struct Room{
	char *description;
	struct Item *items;
	struct Room *north;
	struct Room *south;
	struct Room *east;
	struct Room *west;
};

struct Room *room(char *description, struct Item *items,
                  struct Room *north, struct Room *south,
                  struct Room *east, struct Room *west) {

	struct Room *newRoom = (struct Room*)malloc(sizeof(struct Room));
	newRoom->description = malloc(strlen(description));

	strcpy(newRoom->description, description);
	newRoom->items = items;
	newRoom->north = north;
	newRoom->south = south;
	newRoom->east = east;
	newRoom->west = west;

}

void room_exit_north(struct Room *current, struct Room *other) {
	current->north = other;
}

void room_exit_south(struct Room *current, struct Room *other) {
	current->south = other;
}

void room_exit_east(struct Room *current, struct Room *other) {
	current->east = other;
}

void room_exit_west(struct Room *current, struct Room *other) {
	current->west = other;
}

struct Room *room_north(struct Room *current) {
	return current->north;
}

struct Room *room_south(struct Room *current) {
	return current->south;
}

struct Room *room_east(struct Room *current) {
	return current->east;
}

struct Room *room_west(struct Room *current) {
	return current->west;
}

char *room_description(struct Room *current) {
	return current->description;
}

struct Item *room_items(struct Room *current) {
	return current->items;
}

void look_room(struct Room *current) {

	printf("looks like I'm in the %s\n\n", current->description);
	printf("There's: \n");
	print_items(room_items(current));
	printf("in this room\n\n");

	if(room_north(current) != NULL) { printf("Looks like I can go north\n"); }
	if(room_south(current) != NULL) { printf("Looks like I can go south\n"); }
	if(room_east(current) != NULL) { printf("Looks like I can go east\n"); }
	if(room_west(current) != NULL) { printf("Looks like I can go west\n"); }

	if(strcmp(room_description(current), "Sleeping Quarters") == 0 &&
		current->south == NULL) {
		printf("There's a red door south\n");
	}

	else if(strcmp(room_description(current), "Hall") == 0 &&
					current->north == NULL) {
		printf("There's a blue door north\n");
	}

	else if(strcmp(room_description(current), "HangarA") == 0 &&
					current->east == NULL) {
		printf("There's a green door east\n");
	}

	else if(strcmp(room_description(current), "Escape Pods") == 0) {
		printf("Use the podkey to escape\n");
	}

}

struct Room *go_room(struct Room *current, char *direction) {

	if(strcmp(direction, "north") == 0 && room_north(current) != NULL) {
		return room_north(current);
	}
	
	else if(strcmp(direction, "south") == 0 && room_south(current) != NULL) {
		return room_south(current); 
  }
	
	else if(strcmp(direction, "east") == 0 && room_east(current) != NULL) { 
		return room_east(current);
  }
	
	else if(strcmp(direction, "west") == 0 && room_west(current) != NULL) {
		return room_west(current);
	}
}

struct Room *initial_rooms() {

	struct Item *room_1_items = item("redkey", "use to open red door", NULL);
	struct Item *room_2_items = item("cbox", "a cardboard box", 
															item("helmet", "a pilot's helmet", NULL));
	struct Item *room_3_items = item("sunglasses", "aviator sunglasses", NULL);
	struct Item *room_4_items = item("jerrycan", "container used to hold fuel", NULL);

	struct Room *room_1 = room("Sleeping Quarters", room_1_items, NULL, NULL, NULL, NULL);
	struct Room *room_2 = room("Hall", room_2_items, NULL, NULL, NULL, NULL);
	struct Room *room_3 = room("HangarA", room_3_items, NULL, NULL, NULL, NULL);
	struct Room *room_4 = room("HangarB", room_4_items, NULL, NULL, NULL, NULL);
	struct Room *room_5 = room("Escape Pods", NULL, NULL, NULL, NULL, NULL);

	room_exit_east(room_1, room_2);

	room_exit_east(room_2, room_3);
	room_exit_west(room_2, room_1);

	room_exit_south(room_3, room_4);
	room_exit_west(room_3, room_2);

	room_exit_south(room_4, room_5);
	room_exit_north(room_4, room_3);

	room_exit_north(room_5, room_4);

	return room_1;
}

int use_key(struct Room **current, char *key) {
		
	if(strcmp(room_description(*current), "Sleeping Quarters") == 0 &&
			strcmp(key, "redkey") == 0) {
			
		room_exit_south(*current, room("Cafeteria", item("bluekey", "used to open the blue door", NULL),
															*current, NULL, NULL, NULL));

		printf("the south door is now open\n\n");
		return 0;
	}

	else if(strcmp(room_description(*current), "Hall") == 0 &&
					strcmp(key, "bluekey") == 0) {

	room_exit_north(*current, room("Clinic", item("greenkey", "used to open the green door", NULL),
									NULL, *current, NULL, NULL));
		
		printf("The north door is now open\n\n");
		return 0;
	}

	else if(strcmp(room_description(*current), "HangarA") == 0 &&
					strcmp(key, "greenkey") == 0) {

	room_exit_east(*current, room("Office", item("podkey", "used to activate an escape pod", NULL),
									NULL, NULL, NULL, *current));

		printf("The east door is now open \n\n");
		return 0;
	}

	else if(strcmp(room_description(*current), "Escape Pods") == 0 &&
					strcmp(key, "podkey") == 0) {

		return 1;
	}

	else return 0;

}
