#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stdint.h>
#include "data.h"

//New Version

typedef struct _ll_node_ {
	Data * data;
	struct _ll_node_ * next;
} LlNode;

#if 0
/**
	creates new empty node
*/
#endif
LlNode * ll_node_new();
#if 0
/**
	creates new empty node and add to dest.
*/
#endif
void ll_node_new_dest(LlNode ** dest);

#if 0
/**
	deletes node. It will deletes data too
*/
#endif
void ll_node_free(LlNode **node);
#if 0
/**
	deletes nodes content. It will deletes data too
*/
#endif
void ll_node_clear(LlNode *node);
#if 0
/**
	attach new data to node. Does nothing if data exist.
*/
#endif
void ll_node_attach_data(LlNode *node, Data * data);
#if 0
/**
	attach new data to node. If data exist the new data will be attached and then the old one returned.
*/
#endif
Data * ll_node_attach_data_override(LlNode *node, Data * data);
#if 0
/**
	attach new data to node. If data exist the new data will be attached and then the old one will
	linked to dest pointer.
*/
#endif
void ll_node_attach_data_override_dest(Data **dest, LlNode *node, Data * data);
#if 0
/**
	removes data from node and return the removed data. Returns null if no data exist.
*/
#endif
LlNode * ll_node_copy(LlNode * src);
#if 0
/**
	Copy node src and saves result to dest.
*/
#endif
void ll_node_copy_dest(LlNode ** dest, LlNode * src);
#if 0
/**
	removes data from node and return the removed data. Returns null if no data exist.
*/
#endif
Data * ll_node_detach_data(LlNode *node);
#if 0
/**
	removes data from node and add the removed data to dest. If no data attached NULL will added.
*/
#endif
void ll_node_detach_data_dest(Data ** dest, LlNode *node);


typedef struct {
	LlNode * start;
	LlNode * end;
	unsigned int len;
} LList;

#if 0
/**
	creates new empty list
*/
#endif
LList* llist_new();
void llist_new_dest(LList **list);
#if 0
/**
 delete complete list.
*/
#endif
void llist_free(LList **list);
#if 0
/**
 clears whole list complete list.
*/
#endif
void llist_clear(LList *list);
#if 0
/**
Merges two lists. The first list is the starting list.
*/
#endif
void llist_append_list(LList * list, LList * list2);
#if 0
/**
Add element at end of list.
*/
#endif
void llist_append_node(LList * list, LlNode * newnode);
#if 0
/**
delete node. Deletes node if it exist in list.
*/
#endif
void llist_delete_node(LList * list, LlNode * delnode);
#if 0
/**
delete node after node. Deletes node if it exist in list.
*/
#endif
void llist_delete_node_after(LList * list, LlNode * delnode);
#if 0
/**
delete node after node. Deletes node if it exist in list.
*/
#endif
void llist_delete_node_before(LList * list, LlNode * delnode);
#if 0
/**
	gets the data of given index or NULL
*/
#endif
void* llist_list_get_data(LList *list, uint32_t index);
#if 0
/**
Add element at beginning of list.
*/
#endif
void llist_prepend_node(LList * list, LlNode * newnode);
#if 0
/**
Merges two lists. The second list is the starting list.
*/
#endif
void llist_prepend_list(LList * list, LList * list2);
#if 0
/**
Insert Node after sibling.
*/
#endif
void llist_insert_after(LList * list, LlNode * sibling ,LlNode * newnode);

#if 0
/**
Insert Node before sibling.
*/
#endif
void llist_insert_before(LList * list, LlNode * sibling ,LlNode * newnode);
#if 0
/**
Returns the all found nodes. The result is a linked list with a copy of all found elements. this 
result list will be the response
*/
#endif
LList * llist_search_node_all(LList * list, 
								void * searchdata, bool (*searchmethod)(void * nodedata, void * searchdata));
#if 0
/**
Returns the all found nodes. The result is a linked list with a copy of all found elements. The
Resultlist will add to the resultlistpointer.
*/
#endif
void llist_search_node_all_dest(LList ** resultlist, LList * list, 
								void * searchdata, bool (*searchmethod)(void * nodedata, void * searchdata));
#if 0
/**
returns the first node which data comparing functions returns true. The return value is the found node
or NULL if no node was found.
*/
#endif
LlNode * llist_search_node_first(LList * list, 
								void * searchdata, bool (*searchmethod)(void * nodedata, void * searchdata));
#if 0
/**
returns the first node which data comparing functions returns true. The result value is the found node
or NULL if no node was found and will add to the result pointer.
*/
#endif
void llist_search_node_first_dest(LlNode ** resultnode,LList * list, 
								void * searchdata, bool (*searchmethod)(void * nodedata, void * searchdata));
#if 0
/**
returns the previous node which data comparing functions returns true. The return value is the found node
or NULL if no node was found.
*/
#endif
LlNode * llist_search_previous_node(LList * list, 
								void * searchdata, bool (*searchmethod)(void * nodedata, void * searchdata));
#if 0
/**
returns the previous node which data comparing functions returns true. The result value is the found node
or NULL if no node was found and will add to the result pointer.
*/
#endif
void llist_search_previous_node_dest(LlNode ** resultnode,LList * list, 
								void * searchdata, bool (*searchmethod)(void * nodedata, void * searchdata));


//OLD Version

typedef struct __element {
	void * data;
	struct __element * next;
} element;

typedef struct __linked_list {
	element * start;
	element * end;
	unsigned int len;
} linkedlist;

struct __linked_list_func {
	void * 	(*get)(linkedlist* const list,unsigned int index);
	void 	(*append)(linkedlist* const list, void * data);
	linkedlist * (*new)();
	void (*clear)(linkedlist * list, void (*free_func)(void * ptr));
	void (*delete)(linkedlist * list , void (*free_func)(void * ptr));
	//void (*deleteidx)(linkedlist * const list,unsigned int index);
};

extern const struct __linked_list_func linkedlistutils;

#endif
