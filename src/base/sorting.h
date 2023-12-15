#pragma once

#include <stdlib.h>

typedef int tab_element_t;

void insertion_sort(tab_element_t *array, size_t element_count);
void selection_sort(tab_element_t *array, size_t element_count);
void merge_sort(tab_element_t *array, size_t element_count);
void quick_sort(tab_element_t *array, size_t element_count);