#pragma once

#include <stdbool.h>

#include "types.h"

ll_clist_t ll_clist_next(ll_clist_t);
ll_list_element_t ll_clist_data(ll_clist_t);

void ll_clist_init(ll_clist_t*);
bool ll_clist_is_empty(ll_clist_t);
bool ll_clist_is_full(ll_clist_t);

void ll_clist_foreach(ll_clist_t, void (*)(ll_clist_t));

void ll_clist_alloc_cell(ll_clist_t*);
void ll_clist_free_cell(ll_clist_t*);
void ll_clist_remove_all(ll_clist_t*s);
void ll_clist_first_insert(ll_list_element_t, ll_clist_t*);
void ll_clist_insert_before(ll_list_element_t, ll_clist_t);
void ll_clist_insert_after(ll_list_element_t, ll_clist_t);