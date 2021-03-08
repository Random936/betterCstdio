#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
--------------------------------------------------
    Easy Linked Lists
--------------------------------------------------
*/

typedef struct list_s {
    int valuesize;
    void (*create)();
    void (*insert)();
    void (*remove)();
    void (*print)(struct list_s *self, char *formatter);
    void *head;
} list;

#define declareLinkedList(type, name) \
struct name { \
    type value; \
    struct name *next; \
}; \
 \
void createNode_##name(list *self, type data) { \
 \
    self->valuesize++; \
    struct name *node = malloc(sizeof(struct name)); \
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
void insertNode_##name(list *self, int position, type data) { \
 \
    self->valuesize++; \
    struct name *prev = NULL; \
    struct name *temp = self->head; \
    struct name *insert = malloc(sizeof(struct name)); \
    insert->value = data; \
 \
    for (int i = 0; i < position && temp != NULL; i++) { \
        prev = temp; \
        temp = temp->next; \
    } \
 \
    if (prev == NULL) { \
        insert->next = self->head; \
        self->head = insert; \
    } else { \
        prev->next = insert; \
        insert->next = temp; \
    } \
 \
} \
 \
void removeNode_##name(list *self, int position) { \
    struct name *prev = NULL; \
    struct name *temp = self->head; \
    for (int i = 0; i < position && temp->next != NULL; i++) { \
        prev = temp; \
        temp = temp->next; \
    } \
 \
    if (prev == NULL) { \
        self->head = temp->next; \
    } else if (temp->next != NULL) { \
        prev->next = temp->next; \
    } else { \
        prev->next = NULL; \
    } \
 \
    self->valuesize--; \
    free(temp); \
} \
 \
void print_##name(list *self, char *formatter) { \
    struct name *temp = self->head; \
    while (temp != NULL) { \
        printf(formatter, temp->value); \
        temp = temp->next; \
    } \
} \
 \
list initList_##name() { \
    list list_default = { \
        0, \
        &createNode_##name, \
        &insertNode_##name, \
        &removeNode_##name, \
        &print_##name \
    }; \
    return list_default; \
} \

/*
--------------------------------------------------
    Better Strings
--------------------------------------------------
*/

typedef struct string_s {
    char *value;
    int size;
    void (*print)(struct string_s *self);
    void (*input)(struct string_s *self, int blocksize);
    void (*resize)(struct string_s *self, int newsize);
    int (*length)(struct string_s *self);
    void (*append)(struct string_s *self, char *to_append);
    int (*find)(struct string_s *self, char *to_find, int startpos);
    int *(*findall)(struct string_s *self, char *to_find);
    char *(*substr)(struct string_s *self, int startpos, int endpos);
    void (*replace)(struct string_s *self, char *to_replace, char *replacement);
} string;

string initString(char *initstring);

void string_print(string *self) {
    printf("%s\n", self->value);
}

void string_input(string *self, int blocksize) {
    
    char current;
    int mallocsize = blocksize;
    char *userinput = malloc(sizeof(char) * blocksize);
    int length;
    for (length = 0; (current = getc(stdin)) != '\n'; length++) {
        if (length >= mallocsize - 1) {
            mallocsize += blocksize;
            userinput = realloc(userinput, mallocsize);
        }
        userinput[length] = current;
    } userinput[length] = '\0';

    userinput = realloc(userinput, length);
    free(self->value);
    self->value = userinput;
    self->size = length;
}

void string_resize(string *self, int newsize) {
    self->size = newsize;
    self->value = realloc(self->value, newsize);
}

int string_length(string *self) {
    return strlen(self->value);
}

void string_append(string *self, char *to_append) {

    int appendlen = strlen(to_append);
    int selflen, totallen;

    selflen = self->length(self);
    totallen = appendlen + selflen;
    self->value = realloc(self->value, totallen);
    self->size = totallen;

    for (int i = 0; i <= appendlen; i++) {
        self->value[i + selflen] = to_append[i];
    } self->value[totallen] = '\0';

}

int string_find(string *self, char *to_find, int startpos) {

    if (self->length(self) <= startpos) {
        return -1;
    }

    int findlen = strlen(to_find);

    for (int i = startpos; self->value[i] != '\0'; i++) {
        if (self->value[i] == to_find[0]) {
            int match = 0;
            for ( ; (to_find[match] == self->value[i + match]) && (to_find[match] != '\0'); match++);
            if (match == findlen) {
                return i;
            }
        }
    }

    return -1;
}

int *string_findall(string *self, char *to_find) {

    int findlen = strlen(to_find);
    int *positions = malloc(0);
    int found_num = 0;

    for (int i = 0; self->value[i] != '\0'; i++) {
        if (self->value[i] == to_find[0]) {
            int match = 0;
            for ( ; (to_find[match] == self->value[i + match]) && (to_find[match] != '\0'); match++);
            if (match == findlen) {
                positions = realloc(positions, sizeof(int) * (found_num + 1));
                positions[found_num] = i;
                found_num++;
            }
        }
    }

    return positions;

}

char *string_substring(string *self, int startpos, int endpos) {

    int sublength = endpos - startpos;
    if (startpos > endpos || startpos < 0 || endpos > self->size) {
        fprintf(stderr, "ERROR: Substring start position must be less than the end position.\n");
        return NULL;
    }

    char *returnedstring = malloc(sizeof(char) * sublength);
    for (int i = 0; i < sublength; i++) {
        returnedstring[i] = self->value[startpos + i];
    } returnedstring[sublength] = '\0';

    return returnedstring;
}

void string_replace(string *self, char *to_replace, char *replacement) {

    int value_len = strlen(self->value);
    int to_rep_len = strlen(to_replace);
    int rep_len = strlen(replacement);

    int found_num = 0;
    int *positions = self->findall(self, to_replace);
    for ( ; positions[found_num] != 0; found_num++);
    self->size = value_len - (to_rep_len * found_num) + (rep_len * found_num);
    char *ret_str = malloc(self->size);
    
    int value_pos = 0, ret_pos = 0;
    while (value_pos < value_len) {

        ret_str[ret_pos] = self->value[value_pos];

        if (value_pos == *positions && *positions != 0) {

            for (int i = 0; i < rep_len; i++) {
                ret_str[ret_pos + i] = replacement[i];
            }

            value_pos += to_rep_len;
            ret_pos += rep_len;
            positions++;
        } else {

            value_pos++;
            ret_pos++;
        }
    }

    free(self->value);
    self->value = ret_str;
    
}

string initString(char *initstring) {

    int stringlen = strlen(initstring);

    char *immutablestring = malloc(sizeof(char) * (stringlen + 1));
    for (int i = 0; i < stringlen; i++) {
        immutablestring[i] = initstring[i];
    } immutablestring[stringlen] = '\0';
    
    string string_default = {
        immutablestring,
        stringlen + 1,
        &string_print,
        &string_input,
        &string_resize,
        &string_length,
        &string_append,
        &string_find,
        &string_findall,
        &string_substring,
        &string_replace
    };

    return string_default;
}

/*
--------------------------------------------------
    Better Files
--------------------------------------------------
*/

typedef struct filestream_s {
    char *(*read)(struct filestream_s *self);
    void (*write)(struct filestream_s *self, char *content, int contentsize);
    FILE *desc;
    int size;
} filestream;

char *filestream_read(filestream *self) {

    fseek(self->desc, 0, SEEK_END);
    self->size = ftell(self->desc);
    rewind(self->desc);

    char *filecontent = malloc(self->size);
    fread(filecontent, self->size, 1, self->desc);
    filecontent[self->size] = '\0';
    return filecontent;
}

void filestream_write(filestream *self, char *content, int contentsize) {
    fwrite(content, contentsize, 1, self->desc);
    fseek(self->desc, 0, SEEK_END);
    self->size = ftell(self->desc);
    rewind(self->desc);
}

filestream initFilestream(char *filename, char *options) {

    filestream file_default = {
        &filestream_read,
        &filestream_write
    };

    file_default.desc = fopen(filename, options);

    fseek(file_default.desc, 0, SEEK_END);
    file_default.size = ftell(file_default.desc);
    rewind(file_default.desc);
    
    return file_default;
}
