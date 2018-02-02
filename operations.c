//
// Created by j on 1/28/18.
//

#include <stdio.h>
#include "operations.h"

double addition(struct element *el) {
    double result = 0.0;
    struct element *tmp = el;

    while (tmp != NULL) {
        result += tmp->goodThing;
        tmp = tmp->next;
    }

    return result;
}

double substracion(struct element *el) {
    double result;
    struct element *tmp = el;

    result = tmp->goodThing;
    tmp = tmp->next;

    while (tmp != NULL) {
        result -= tmp->goodThing;
        tmp = tmp->next;
    }

    return result;
}

void descendingSotring(struct element *el) {
    int swapped, i;
    struct element *ptr1;
    struct element *lptr = NULL;
/*
    *//* Checking for empty list *//*
    if (ptr1 == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = el;

        while (ptr1->next != lptr) {
            if (ptr1->goodThing < ptr1->next->goodThing) {
                swap(ptr1->next, ptr1);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
*/

    ptr1 = el;
    for(; ptr1->next != NULL; ptr1 = ptr1->next)
    {
        for(lptr = ptr1->next; lptr != (struct element*)NULL; lptr = lptr->next)
        {
            if(ptr1->goodThing < lptr->goodThing)
            {
                int temp = (int) ptr1->goodThing;
                ptr1->goodThing = lptr->goodThing;
                lptr->goodThing = temp;
            }
        }
    }

}

void ascendingSorting(struct element *el) {
    int swapped, i;
    struct element *ptr1;
    struct element *lptr = NULL;

    /* Checking for empty list */
    if (ptr1 == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = el;

        while (ptr1->next != lptr) {
            if (ptr1->goodThing > ptr1->next->goodThing) {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);


}


/* function to swap goodThing of two element a and b*/
void swap(struct element *a, struct element *b) {
    double temp = a->goodThing;
    a->goodThing = b->goodThing;
    b->goodThing = temp;
}