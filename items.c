#include "items.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Item *item(char *name, char *description, struct Item *next) {
  
	struct Item *newItem = (struct Item*)malloc(sizeof(struct Item));
	newItem->name = malloc(strlen(name));
	newItem->description = malloc(strlen(description));
  
	strcpy(newItem->name, name);
	strcpy(newItem->description, description);
	newItem->next = next;

}

char *item_name(struct Item *item) {
	return item->name;
}

char *item_description(struct Item * item) {
	return item->description;
}

struct Item *item_next(struct Item * item) {
	return item->next;
}

struct Item *insert_item(struct Item *head, struct Item *newHead) {
	newHead->next = head;
	return newHead;
}

struct Item *item_copy(struct Item * source) {
	struct Item *copy = item(item_name(source), item_description(source), NULL);
	return copy;
}

struct Item *item_take(struct Item ** root, char * item) {

  struct Item *temp;

  if(strcmp(item_name(*root), item) == 0) {
    temp = item_copy(*root);
    *root = item_next(*root);
    return temp;
    }

  else {
    for(struct Item *node = *root; item_next(node) != NULL; node = item_next(node)) {

      if(strcmp(item_name(item_next(node)), item) == 0) {

        temp = item_copy(item_next(node));

        if(item_next(item_next(node)) == NULL) { 
          node->next = NULL;
          return temp;
        }

        else { 
          node->next = node->next->next;
          return temp;
        }

        break;
      }

    }
  }

  return NULL;
}

void print_items(struct Item *root) {

	if(root == NULL) {
		printf("There are no items here\n");
	}
	for(struct Item *node = root; node != NULL; node = node->next) {
		printf("%s\n", item_name(node));
	}

}
