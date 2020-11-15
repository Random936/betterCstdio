#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct string_s {
    char *value;
    void (*print)(struct string_s *);
    int (*length)(struct string_s *);
    void (*append)(struct string_s *, char*);
    int (*find)(struct string_s *, char *);
    char *(*substr)(struct string_s *, int, int);
    void (*replace)(struct string_s *, char *, char *);
} string;

string allocateString(char *initstring);

void stringprint(string *this) {
    printf("%s\n", this->value);
}

int stringlength(string *this) {
    int length;
    for (length = 0; this->value[length] != 0; length++);
    return length;
}

void stringappend(string *this, char *to_append) {

    int appendlen, thislen, totallen;
    for (appendlen = 0; to_append[appendlen] != '\0'; appendlen++);
    thislen = this->length(this);
    totallen = appendlen + thislen;

    char *tempptr = malloc(sizeof(char) * totallen + 1);
    for (int i = 0; i <= thislen; i++) {
        tempptr[i] = this->value[i];
    }
    for (int i = 0; i <= appendlen; i++) {
        tempptr[i + thislen] = to_append[i];
    } tempptr[totallen] = '\0';

    free(this->value);
    this->value = tempptr;
}

int stringfind(string *this, char *to_find) {

    int findlen, match;
    for (findlen = 0; to_find[findlen] != '\0'; findlen++);

    for (int i = 0; this->value[i] != '\0'; i++) {
        if (this->value[i] == to_find[0]) {
            for (match = 0; (to_find[match] == this->value[i + match]) && (to_find[match] != '\0'); match++);
            if (match >= findlen) {
                return i;
            }
        }
    }

    return -1;
}

char *stringsubstring(string *this, int startpos, int endpos) {

    int sublength = endpos - startpos;
    char *returnedstring = malloc(sizeof(char) * sublength);
    if (startpos > endpos) {
        printf("ERROR: Substring start position must be less than the end position.\n");
        return NULL;
    }
    for (int i = 0; i < sublength; i++) {
        returnedstring[i] = this->value[startpos + i];
    } returnedstring[sublength] = '\0';

    return returnedstring;
}

void stringreplace(string *this, char *to_replace, char *replacement) {

    int to_replace_len, foundpos;
    for (to_replace_len = 0; to_replace[to_replace_len] != '\0'; to_replace_len++);

    string returnedstring = allocateString("");
    while ((foundpos = this->find(this, to_replace)) != -1) {
        char *substring = this->substr(this, 0, foundpos);
        returnedstring.append(&returnedstring, substring);
        free(substring);
        returnedstring.append(&returnedstring, replacement);
        this->value += foundpos + to_replace_len;
    }

    if (this->value[0] != '\0') {
        char *substring = this->substr(this, 0, this->length(this));
        returnedstring.append(&returnedstring, substring);
        free(substring);
    }

    free(this->value);
    this->value = returnedstring.value;
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
        &stringlength,
        &stringappend,
        &stringfind,
        &stringsubstring,
        &stringreplace
    };

    return string_default;
}