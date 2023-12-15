#pragma once

typedef int ll_list_element_t;

typedef struct lcell {
    ll_list_element_t data;
    struct lcell *next;
} *ll_list_t;

typedef struct {
    ll_list_t head;
    ll_list_t tail;
    int size;
} ll_dr_list_t;

typedef struct clcell {
    ll_list_element_t data;
    struct clcell *next;
} *ll_clist_t;

typedef struct {
    ll_clist_t head;
    ll_clist_t tail;
    int size;
} ll_dr_clist_t;