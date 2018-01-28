//
// Created by j on 1/27/18.
//

#ifndef SERWER_FUNCTIONS_H
#define SERWER_FUNCTIONS_H

#include "struct.h"

char **str_split(char *a_str, const char a_delim);

char *pickOneOperation(char **pString, int messageSize);

int getMessageSize(char **pString);

char *splitListAgain(struct element *el);

#endif //SERWER_FUNCTIONS_H
