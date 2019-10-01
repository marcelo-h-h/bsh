#ifndef PARSER_PUBLIC
#define PARSER_PUBLIC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./datatypes.h"

string_t  get_line();
string_t* split_line(string_t);

#endif