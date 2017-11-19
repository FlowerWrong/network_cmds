//
//  util.c
//  route
//
//  Created by king Yang on 2017/11/19.
//

#include "util.h"

void print_argv(int argc, char **argv) {
    printf("print argc and argv start ---------\n");
    int i;
    printf("argc %d \n", argc);
    for(i=0; i < argc-1; i++) {
        printf("%s\n", argv[i]);
    }
    printf("print argc and argv end -----------\n");
}


int cmdlineno;
/* Like glibc getline but handle continuation lines and comments */
ssize_t getcmdline(char **linep, size_t *lenp, FILE *in)
{
    ssize_t cc;
    char *cp;
    
    cc = getline(linep, lenp, in);
    if (cc < 0)
        return cc;    /* eof or error */
    ++cmdlineno;
    
    cp = strchr(*linep, '#');
    if (cp)
        *cp = '\0';
    
    while ((cp = strstr(*linep, "\\\n")) != NULL) {
        char *line1 = NULL;
        size_t len1 = 0;
        ssize_t cc1;
        
        cc1 = getline(&line1, &len1, in);
        if (cc1 < 0) {
            fprintf(stderr, "Missing continuation line\n");
            return cc1;
        }
        
        ++cmdlineno;
        *cp = 0;
        
        cp = strchr(line1, '#');
        if (cp)
            *cp = '\0';
        
        *lenp = strlen(*linep) + strlen(line1) + 1;
        *linep = realloc(*linep, *lenp);
        if (!*linep) {
            fprintf(stderr, "Out of memory\n");
            *lenp = 0;
            return -1;
        }
        cc += cc1 - 2;
        strcat(*linep, line1);
        free(line1);
    }
    return cc;
}

/* split command line into argument vector */
int makeargs(char *line, char *argv[], int maxargs)
{
    static const char ws[] = " \t\r\n";
    char *cp;
    int argc = 0;
    
    for (cp = line + strspn(line, ws); *cp; cp += strspn(cp, ws)) {
        if (argc >= (maxargs - 1)) {
            fprintf(stderr, "Too many arguments to command\n");
            exit(1);
        }
        
        /* word begins with quote */
        if (*cp == '\'' || *cp == '"') {
            char quote = *cp++;
            
            argv[argc++] = cp;
            /* find ending quote */
            cp = strchr(cp, quote);
            if (cp == NULL) {
                fprintf(stderr, "Unterminated quoted string\n");
                exit(1);
            }
            *cp++ = 0;
            continue;
        }
        
        argv[argc++] = cp;
        /* find end of word */
        cp += strcspn(cp, ws);
        *cp++ = 0;
    }
    argv[argc] = NULL;
    
    return argc;
}
