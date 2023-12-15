#include <err.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "clist.h"
#include "types.h"

ll_clist_t ll_clist_next(ll_clist_t l) {
    return l->next;
}

ll_list_element_t ll_clist_data(ll_clist_t l) {
    return l->data;
}

void ll_clist_init(ll_clist_t *l) {
    *l = NULL;
}

bool ll_clist_is_empty(ll_clist_t l) {
    return l == NULL;
}

bool ll_clist_is_full(ll_clist_t l) {
    return false;
}

void ll_clist_foreach(ll_clist_t l, void (*process)(ll_clist_t)) {
    ll_clist_t tmp;
    tmp = l;

    do {
        process(tmp);
        tmp = ll_clist_next(tmp);
    } while (tmp != l);
}

void ll_clist_alloc_cell(ll_clist_t *l) {
    *l = (ll_clist_t) malloc(sizeof(struct clcell));

    if (*l == NULL) {
        err(1, "An error occured when trying to allocate memory.");
    }
}

void ll_clist_free_cell(ll_clist_t *l) {
    free(*l);
    *l = NULL;
}

void ll_clist_remove_all(ll_clist_t *l) {
    ll_clist_t tmp1, tmp2;
    tmp1 = ll_clist_next(*l);

    while (tmp1 != *l) {
        tmp2 = tmp1;
        tmp1 = ll_clist_next(tmp2);
        ll_clist_free_cell(&tmp2);
    }

    ll_clist_free_cell(l);
}

void ll_clist_first_insert(ll_list_element_t elt, ll_clist_t *l) {
    ll_clist_alloc_cell(l);
    (*l)->data = elt;
    (*l)->next = *l;
}

void ll_clist_insert_before(ll_list_element_t elt, ll_clist_t l) {
    ll_clist_t node;
    ll_clist_alloc_cell(&node);

    ll_clist_t insertionNode;
    insertionNode = ll_clist_next(l);
    while (ll_clist_next(insertionNode) != l) {
        insertionNode = ll_clist_next(insertionNode);
    }

    node->data = elt;
    node->next = l;
    insertionNode->next = node;
}

void ll_clist_insert_after(ll_list_element_t elt, ll_clist_t l) {
    ll_clist_t node;
    ll_clist_alloc_cell(&node);

    node->data = elt;
    node->next = ll_clist_next(l);
    l->next = node;
}