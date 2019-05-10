#ifndef items_h
#define items_h

struct Item{
  char *name;
  char *description;
  struct Item *next;
};

struct Item *item(char *name, char *description, struct Item *next);

//extract info from item struct
char *item_name(struct Item * item);
char *item_description(struct Item * item);
struct Item *item_next(struct Item * item);

//sets the next item in an item struct
struct Item *insert_item(struct Item *head, struct Item *newHead);

//helper function used in item take, takes an item from a list and
//returns it as a standalone item
struct Item *item_copy(struct Item * source);

//returns and removes an item from a list of items
struct Item *item_take(struct Item ** root, char * item);

//prints the list of items
void print_items(struct Item *root);

#endif
