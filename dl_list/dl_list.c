#include "dl_list.h"

static void __dl_list_reset(DlList *list) {
	list->last = NULL;
	list->first = NULL;
	list->cnt = 0;
}

static DlListItem* __dl_list_item_new(void *data) {
	DlListItem* newitem = malloc(sizeof(DlListItem));
	if(newitem) {
		newitem->data = data;
		newitem->next = NULL;
		newitem->prev = NULL;
	}
	return newitem;
}

static void __dl_list_item_free(DlListItem **item) {
	if ( item != NULL && *item != NULL ) {
		DlListItem *to_delete = *item;
		free(to_delete);
		*item = NULL;
	}
}

static void __dl_list_add_first_node(DlList *list, DlListItem* node) {
	list->first = node;
	list->last = node;
}

static void __dl_list_append_node(DlListItem* basenode, DlListItem* newnode) {
	
	newnode->prev = basenode;

	if (basenode->next != NULL) {
		newnode->next = basenode->next;
		basenode->next->prev = newnode;
	} 

	basenode->next = newnode;

}

static void __dl_list_prepend_node(DlListItem* basenode, DlListItem* newnode) {
	
	newnode->next = basenode;

	if (basenode->prev != NULL) {
		newnode->prev = basenode->prev;
		basenode->prev->next = newnode;
	}

	basenode->prev = newnode;

}

static void __dl_list_remove_node(DlList *list, DlListItem* node) {
	
	if (list->cnt == 1) {
		__dl_list_item_free(&node);
		__dl_list_reset(list);
	} else if (list->cnt > 1) {
		if (node->prev == NULL) {
			list->first = node->next;
			list->first->prev = NULL;
		} else if (node->next == NULL) {
			node->prev->next = NULL;
			list->last = node->prev;
		} else {
			DlListItem* next = node->next;
			DlListItem* prev = node->prev;
			prev->next = next;
			next->prev = prev;
		}
		__dl_list_item_free(&node);
		--list->cnt;
	}

}

static DlListItem* __search_node_by_data(DlList *list, void *data) {
	DlListItem* result = NULL;
	DlListItem* cur_node = list->first;

	while(cur_node != NULL) {
		if ( cur_node->data == data ) {
			result = cur_node;
			break;
		}
		cur_node = cur_node->next;
	}

	return result;
}

static DlListItem* __search_node_by_idx(DlList *list, uint32_t idx) {
	DlListItem* result = NULL;
	DlListItem* cur_node = list->first;

	if (idx < list->cnt) {
		
		uint32_t cur_idx = -1;

		while(cur_node != NULL) {
			++cur_idx;
			if ( cur_idx == idx ) {
				result = cur_node;
				break;
			}
			cur_node = cur_node->next;
		}
	}

	return result;
}

static void __dl_list_clear(DlList* list) {
	DlListItem* cur_item = list->first;
	DlListItem* tmp_item = NULL;

	while(cur_item != NULL) {
		tmp_item = cur_item->next;
		__dl_list_item_free(&cur_item);
		cur_item = tmp_item;
	}

	__dl_list_reset(list);
}

#if 0
//###############################################################################################################
//Eof private Section
//###############################################################################################################
#endif

DlList* dl_list_new() {
	DlList *newlist = malloc(sizeof(DlList));
	if ( newlist ) {
		__dl_list_reset(newlist);
	}

	return newlist;
}

void dl_list_free(DlList**list) {  
	if ( list != NULL && *list != NULL ) {
		DlList *to_delete = *list;
		
		__dl_list_clear(to_delete);

		free(to_delete);
		*list = NULL;
	}
}

void dl_list_clear(DlList* list) {
	__dl_list_clear(list);
}

void dl_list_append(DlList *list, void *data) { 
	if (list != NULL) {
		DlListItem* newitem = __dl_list_item_new(data);

		if (list->cnt == 0) {
			__dl_list_add_first_node(list, newitem);
		} else {
			__dl_list_append_node(list->last, newitem);
			list->last = newitem;
		}

		++list->cnt;
	}
}

void dl_list_prepend(DlList *list, void *data) {  

	if (list != NULL) {
		DlListItem* newitem = __dl_list_item_new(data);

		if (list->cnt == 0) {
			__dl_list_add_first_node(list, newitem);
		} else {
			__dl_list_prepend_node(list->first, newitem);
			list->first = newitem;
		}

		++list->cnt;
	}

}

void dl_list_insert_prepend(DlList *list, void *sibling, void *value) {  
	if ( list != NULL ) {
		DlListItem* sibl_node = __search_node_by_data(list, sibling);
		if (sibl_node != NULL) {
			DlListItem* newitem = __dl_list_item_new(value);

			__dl_list_prepend_node(sibl_node, newitem);

			++list->cnt;
		}
	}
}

void dl_list_insert_append(DlList *list, void *sibling, void *value) {  
	if ( list != NULL ) {
		DlListItem* sibl_node = __search_node_by_data(list, sibling);
		if (sibl_node != NULL) {
			DlListItem* newitem = __dl_list_item_new(value);

			__dl_list_append_node(sibl_node, newitem);
			
			++list->cnt;
		}
	}
}

void dl_list_insert_prepend_idx(DlList *list, uint32_t index, void *value) {  
	if ( list != NULL ) {
		DlListItem* found = __search_node_by_idx(list, index);

		if (found != NULL) {
			DlListItem* newitem = __dl_list_item_new(value);

			__dl_list_prepend_node(found, newitem);

			++list->cnt;
		}

	}	
}

void dl_list_insert_append_idx(DlList *list, uint32_t index, void *value) {  
	if ( list != NULL ) {
		DlListItem* found = __search_node_by_idx(list, index);

		if (found != NULL) {
			DlListItem* newitem = __dl_list_item_new(value);

			__dl_list_append_node(found, newitem);

			++list->cnt;
		}

	}	
}

void* dl_list_get(DlList *list, uint32_t index) { 
	void *result = NULL;

	if ( list != NULL ) {
		DlListItem* found = __search_node_by_idx(list, index);
		if (found) {
			result = found->data;
		}
	}

	return result;
}



void* dl_list_remove(DlList *list, uint32_t index) {  
	void *result = NULL;

	if ( list != NULL ) {
		DlListItem* found = __search_node_by_idx(list, index);
		if (found) {
			result = found->data;
			__dl_list_remove_node(list, found);
		}
	}

	return result;
}

void dl_list_remove_free(DlList *list, uint32_t index, void (freefunc)(void *data)) {  
	
	if ( list != NULL ) {
		DlListItem* found = __search_node_by_idx(list, index);
		if (found) {

			if(freefunc != NULL) {
				freefunc(found->data);
			} else {
				free(found->data);
			}
			__dl_list_remove_node(list, found);
		}
	}

}

void* dl_list_search_once(DlList *list, void *search_data, bool (*searchfunc)(void*item, void *search_data)) {  
	void *result = NULL;

	DlListItem* cur_node = list->first;

	while(cur_node != NULL) {
		if ( searchfunc(cur_node->data, search_data) ) {
			result = cur_node->data;
			break;
		}
		cur_node = cur_node->next;
	}

	return result; 
}

int dl_list_search_once_idx(DlList *list, void *search_data, bool (*searchfunc)(void*item, void *search_data)) {
	int result = -1;
	bool found = false;

	DlListItem* cur_node = list->first;

	while(cur_node != NULL) {
		++result;
		if ( searchfunc(cur_node->data, search_data) ) {
			found = true;
			break;
		}
		cur_node = cur_node->next;
	}

	return (found ? result : -1 ); 
}

DlList* dl_list_search(DlList *list, void *search_data, bool (*searchfunc)(void*item, void *search_data)) {  
	DlList *result = dl_list_new();

	DlListItem* cur_node = list->first;

	while(cur_node != NULL) {
		if ( searchfunc(cur_node->data, search_data) ) {
			dl_list_append(result, cur_node->data);
		}
		cur_node = cur_node->next;
	}

	return result; 
}

void dl_list_each(DlList *list, EACH_FUNC eachfunc) {

	DlListItem* cur_node = list->first;

	while(cur_node != NULL) {

		eachfunc(&cur_node->data);
		
		cur_node = cur_node->next;
	
	}

}

void  dl_list_each_data(DlList *list, void* eachdata, EACH_FUNC_DATA eachfunc) {
	DlListItem* cur_node = list->first;

	while(cur_node != NULL) {

		eachfunc(&cur_node->data, eachdata);
		
		cur_node = cur_node->next;
	
	}
}