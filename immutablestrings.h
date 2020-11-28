#pragma once
#include <stdio.h>
#include <stdlib.h>

/*
--------------------------------------------------
    Easy Linked Lists
--------------------------------------------------
*/

typedef struct list_s {
    int valuesize;
    void (*createNode)(struct list_s *self, ...);
    void (*print)(struct list_s *self, char *formatter);
    void *head;
} list;

#define declareLinkedList(type, list_node_s) \
struct list_node_s { \
    type value; \
    struct list_node_s *next; \
}; \
 \
void list_createNode(list *self, type data) { \
 \
    self->valuesize++; \
    struct list_node_s *node = malloc(sizeof(struct list_node_s)); \
    node->value = data; \
 \
    if (self->head == NULL) { \
        node->next = NULL; \
        self->head = node; \
    } else { \
        node->next = self->head; \
        self->head = node; \
    } \
} \
 \
void list_print(list *self, char *formatter) { \
    struct list_node_s *temp = self->head; \
    while (temp != NULL) { \
        printf(formatter, temp->value); \
        temp = temp->next; \
    } \
} \
 \
list initList() { \
 \
    list list_default = { \
        0, \
        &list_createNode, \
        &list_print \
    }; \
    return list_default; \
}

/*
--------------------------------------------------
    Better Strings
--------------------------------------------------
*/

typedef struct string_s {
    char *value;
    void (*print)(struct string_s *self);
    void (*input)(struct string_s *self, int blocksize);
    int (*length)(struct string_s *self);
    void (*append)(struct string_s *self, char *to_append);
    int (*find)(struct string_s *self, char *to_find);
    char *(*substr)(struct string_s *self, int startpos, int endpos);
    void (*replace)(struct string_s *self, char *to_replace, char *replacement);
} string;

string initString(char *initstring);

void string_print(string *self) {
    printf("%s\n", self->value);
}

void string_input(string *self, int blocksize) {
    
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

int string_length(string *self) {
    int length;
    for (length = 0; self->value[length] != 0; length++);
    return length;
}

void string_append(string *self, char *to_append) {

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

int string_find(string *self, char *to_find) {

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

char *string_substring(string *self, int startpos, int endpos) {

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

void string_replace(string *self, char *to_replace, char *replacement) {

    int to_replace_len, foundpos;
    for (to_replace_len = 0; to_replace[to_replace_len] != '\0'; to_replace_len++);

    string returnedstring = initString("");
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

string initString(char *initstring) {

    int stringlen;
    for (stringlen = 0; initstring[stringlen] != '\0'; stringlen++);

    char *immutablestring = malloc(sizeof(char) * (stringlen + 1));
    for (int i = 0; i < stringlen; i++) {
        immutablestring[i] = initstring[i];
    } immutablestring[stringlen] = '\0';
    
    string string_default = {
        immutablestring,
        &string_print,
        &string_input,
        &string_length,
        &string_append,
        &string_find,
        &string_substring,
        &string_replace
    };

    return string_default;
}