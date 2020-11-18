#pragma once
#include <stdio.h>
#include <stdlib.h>


/*
--------------------------------------------------
    Easy Vectors
--------------------------------------------------
*/


/*
--------------------------------------------------
    Better Strings
--------------------------------------------------
*/

typedef struct string_s {
    char *value;
    void (*print)(struct string_s *);
    void (*input)(struct string_s *, int);
    int (*length)(struct string_s *);
    void (*append)(struct string_s *, char*);
    int (*find)(struct string_s *, char *);
    char *(*substr)(struct string_s *, int, int);
    void (*replace)(struct string_s *, char *, char *);
} string;

string allocateString(char *initstring);

void stringprint(string *self) {
    printf("%s\n", self->value);
}

void stringinput(string *self, int blocksize) {
    
    FILE *stdinfd = stdin;
    char current;
    int mallocsize = blocksize;
    char *userinput = malloc(sizeof(char) * mallocsize);

    int length;
    for (length = 0; (current = getc(stdin)) != '\n'; length++) {
        if (length >= mallocsize - 1) {
            mallocsize += blocksize;
            userinput = realloc(userinput, sizeof(char) * mallocsize);
        }
        userinput[length] = current;
    } userinput[length] = '\0';

    free(self->value);
    self->value = userinput;
}

int stringlength(string *self) {
    int length;
    for (length = 0; self->value[length] != 0; length++);
    return length;
}

void stringappend(string *self, char *to_append) {

    int appendlen, selflen, totallen;
    for (appendlen = 0; to_append[appendlen] != '\0'; appendlen++);
    selflen = self->length(self);
    totallen = appendlen + selflen;

    char *tempptr = malloc(sizeof(char) * totallen + 1);
    for (int i = 0; i <= selflen; i++) {
        tempptr[i] = self->value[i];
    }
    for (int i = 0; i <= appendlen; i++) {
        tempptr[i + selflen] = to_append[i];
    } tempptr[totallen] = '\0';

    free(self->value);
    self->value = tempptr;
}

int stringfind(string *self, char *to_find) {

    int findlen, match;
    for (findlen = 0; to_find[findlen] != '\0'; findlen++);

    for (int i = 0; self->value[i] != '\0'; i++) {
        if (self->value[i] == to_find[0]) {
            for (match = 0; (to_find[match] == self->value[i + match]) && (to_find[match] != '\0'); match++);
            if (match >= findlen) {
                return i;
            }
        }
    }

    return -1;
}

char *stringsubstring(string *self, int startpos, int endpos) {

    int sublength = endpos - startpos;
    char *returnedstring = malloc(sizeof(char) * sublength);
    if (startpos > endpos) {
        printf("ERROR: Substring start position must be less than the end position.\n");
        return NULL;
    }
    for (int i = 0; i < sublength; i++) {
        returnedstring[i] = self->value[startpos + i];
    } returnedstring[sublength] = '\0';

    return returnedstring;
}

void stringreplace(string *self, char *to_replace, char *replacement) {

    int to_replace_len, foundpos;
    for (to_replace_len = 0; to_replace[to_replace_len] != '\0'; to_replace_len++);

    string returnedstring = allocateString("");
    while ((foundpos = self->find(self, to_replace)) != -1) {
        char *substring = self->substr(self, 0, foundpos);
        returnedstring.append(&returnedstring, substring);
        free(substring);
        returnedstring.append(&returnedstring, replacement);
        self->value += foundpos + to_replace_len;
    }

    if (self->value[0] != '\0') {
        char *substring = self->substr(self, 0, self->length(self));
        returnedstring.append(&returnedstring, substring);
        free(substring);
    }

    free(self->value);
    self->value = returnedstring.value;
}

string allocateString(char *initstring) {

    int stringlen;
    for (stringlen = 0; initstring[stringlen] != '\0'; stringlen++);

    char *immutablestring = malloc(sizeof(char) * (stringlen + 1));
    for (int i = 0; i < stringlen; i++) {
        immutablestring[i] = initstring[i];
    } immutablestring[stringlen] = '\0';
    

    string string_default = {
        immutablestring,
        &stringprint,
        &stringinput,
        &stringlength,
        &stringappend,
        &stringfind,
        &stringsubstring,
        &stringreplace
    };

    return string_default;
}