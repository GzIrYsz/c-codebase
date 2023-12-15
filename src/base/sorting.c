#include "sorting.h"

void insertion_sort(tab_element_t *array, size_t element_count) {
    for (int i = 1; i < element_count; i++) {
        int j = i;
        while (j > 0 && array[j] < array[j-1]) {
            tab_element_t tmp;
            tmp = array[j];
            array[j] = array[j-1];
            array[j-1] = tmp;
            j--;
        }
    }
}

void selection_sort(tab_element_t *array, size_t element_count);
void merge_sort(tab_element_t *array, size_t element_count);
void quick_sort(tab_element_t *array, size_t element_count);