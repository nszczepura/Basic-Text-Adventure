#ifndef rooms_h
#define rooms_h

#include "items.h"

struct Room;

struct Room *room(char *description, struct Item *items,
                   struct Room *north, struct Room *south,
                   struct Room *east, struct Room *west);

//assign the room exits
void room_exit_north(struct Room *current, struct Room *other);
void room_exit_south(struct Room *current, struct Room *other);
void room_exit_east(struct Room *current, struct Room *other);
void room_exit_west(struct Room *current, struct Room *other);

//returns the various exits
struct Room *room_north(struct Room *current);
struct Room *room_south(struct Room *current);
struct Room *room_east(struct Room *current);
struct Room *room_west(struct Room *current);

char *room_description(struct Room *current);

struct Item *room_items(struct Room *current);

//prints a description of the room
void look_room(struct Room *current);

//prints the current rooms items
struct Item *room_items(struct Room *current);

//initializes the rooms and their respective items
//the game starts with 5 rooms but the
//keys open up 3 more
struct Room *initial_rooms();

//used to change the players location
struct Room *go_room(struct Room *current, char *direction);

//opens up rooms depending on the players location
//and the key used
int use_key(struct Room **current, char *key);

#endif
