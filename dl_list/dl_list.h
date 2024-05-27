#ifndef DL_LIST_H
#define DL_LIST_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct __DlListItem {
    void *data;
    struct __DlListItem *next;
    struct __DlListItem *prev;
} DlListItem;

typedef struct {
    uint32_t cnt;
    DlListItem *first;
    DlListItem *last;
} DlList;

typedef void (*EACH_FUNC)(void **data);
typedef void (*EACH_FUNC_DATA)(void **data, void *eachdata);

DlList* dl_list_new();
void dl_list_free(DlList**list);

void dl_list_clear(DlList* list);
void dl_list_append(DlList *list, void *data);
void dl_list_prepend(DlList *list, void *data);
void dl_list_insert_prepend(DlList *list, void *sibling, void *value);
void dl_list_insert_append(DlList *list, void *sibling, void *value);
void dl_list_insert_prepend_idx(DlList *list, uint32_t index, void *value);
void dl_list_insert_append_idx(DlList *list, uint32_t index, void *value);
void* dl_list_get(DlList *list, uint32_t index);
void* dl_list_remove(DlList *list, uint32_t index);
void  dl_list_remove_free(DlList *list, uint32_t index, void (freefunc)(void *data));
void* dl_list_search_once(DlList *list, void *search_data, bool (*searchfunc)(void*item, void *search_data));
int   dl_list_search_once_idx(DlList *list, void *search_data, bool (*searchfunc)(void*item, void *search_data));
DlList* dl_list_search(DlList *list, void *search_data, bool (*searchfunc)(void*item, void *search_data));
void  dl_list_each(DlList *list, EACH_FUNC eachfunc);
void  dl_list_each_data(DlList *list, void* eachdata, EACH_FUNC_DATA eachfunc);

#endif
