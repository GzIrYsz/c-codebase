#include <cstdlib>
#include <iostream>
#include <string>

extern "C" {
#include "../../src/base/sorting.h"
}

using namespace std;

void populate_tab(tab_element_t *array, size_t *element_count);

int main(int argc, char **argv) {
    insertion_sort();
    return EXIT_SUCCESS;
}

void populate_tab(tab_element_t *array, size_t *element_count) {
    char input;
    cin >> input;
    while (input != 'q') {
        if (isdigit(input)) {
            int t = input;
        }
        array[*element_count] = input;
    }
}