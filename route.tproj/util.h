//
//  util.h
//  route
//
//  Created by king Yang on 2017/11/19.
//

#ifndef util_h
#define util_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_argv(int argc, char **argv);

ssize_t getcmdline(char **linep, size_t *lenp, FILE *in);

int makeargs(char *line, char *argv[], int maxargs);

#endif /* util_h */
