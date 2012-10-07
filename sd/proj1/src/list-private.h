#ifndef _LIST_PRIVATE_H
#define _LIST_PRIVATE_H

#include "entry.h"

/*
node of a linked list. it contains an entry an a pointer to the next entry position
*/
struct node_t {
	struct entry_t *entry;
	struct node_t *next;
};

/*
list that has an header a tail and the size of the list.
*/
struct list_t {
	struct node_t *header;
	int size;
};

#endif
