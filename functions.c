//
// Created by j on 1/27/18.
//

#include "functions.h"
#include "operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char **str_split(char *a_str, const char a_delim) {
    char **result = 0;
    size_t count = 0;
    char *tmp = a_str;
    char *last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp) {
        if (a_delim == *tmp) {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char *) * count);

    if (result) {
        size_t idx = 0;
        char *token = strtok(a_str, delim);

        while (token) {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}


char *pickOneOperation(char **pString, int messageSize) {
    printf("Operation sign => [%s]\n", *pString);

    int i;
    struct element *nextForOperation = NULL;
    char *bufferToSend = malloc(0);

    for (i = 1; i < messageSize; i++) {
        struct element *tmpElement = (struct element *) malloc(sizeof(struct element));
        tmpElement->goodThing = atof(pString[i]);
        tmpElement->next = nextForOperation;
        nextForOperation = tmpElement;
    }
    if (strcmp(pString[0], "+") == 0) {
        double result = addition(nextForOperation);
        printf("Result = %f", result);
    } else if (strcmp(pString[0], "-") == 0) {
        double result = substracion(nextForOperation);
        printf("Result = %f", result);
    } else if (strcmp(pString[0], ">") == 0) {
        ascendingSorting(nextForOperation);
        printList(nextForOperation);
        bufferToSend = splitListAgain(nextForOperation);
    } else if (strcmp(pString[0], "<") == 0) {
        descendingSotring(nextForOperation);
        printList(nextForOperation);
        bufferToSend = splitListAgain(nextForOperation);
    }

    return bufferToSend;
}

int getMessageSize(char **pString) {
    int size = 0;

    if (!pString) return 0;

    while (*(pString + size) != NULL) {
        size++;
    }


    return size;
}


char *splitListAgain(struct element *el) {
    struct element *tmp = el;

    char *output = malloc(0);

    while (tmp != NULL) {
        char tempBuff[sizeof(double)];
        sprintf(tempBuff, "%.2f", tmp->goodThing);
        strcat(tempBuff, " ");
        strcat(output, tempBuff);
        tmp = tmp->next;
    }

    return output;
}


/* Function to print nodes in a given linked list */
void printList(struct element *start) {
    struct element *temp = start;
    printf("\n");
    while (temp != NULL) {
        printf("%0.2f ", temp->goodThing);
        temp = temp->next;
    }
}