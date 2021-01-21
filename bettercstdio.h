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
    int (*find)(struct string_s *self, char *to_find);
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
    int length;
    for (length = 0; self->value[length] != 0; length++);
    return length;
}

void string_append(string *self, char *to_append) {

    int appendlen, selflen, totallen;
    for (appendlen = 0; to_append[appendlen] != '\0'; appendlen++);
    selflen = self->length(self);
    totallen = appendlen + selflen;

    self->size = sizeof(char) * totallen;
    char *tempptr = malloc(self->size);
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
    if (startpos > endpos || startpos < 0 || endpos > self->size) {
        printf("ERROR: Substring start position must be less than the end position.\n");
        return NULL;
    }

    char *returnedstring = malloc(sizeof(char) * sublength);

    for (int i = 0; i < sublength; i++) {
        returnedstring[i] = self->value[startpos + i];
    } returnedstring[sublength] = '\0';

    return returnedstring;
}

void string_replace(string *self, char *to_replace, char *replacement) {

    int to_replace_len, replacement_length, found_position;
    for (to_replace_len = 0; to_replace[to_replace_len] != '\0'; to_replace_len++);
    for (replacement_length = 0; replacement[replacement_length] != '\0'; replacement_length++);

    int returnedsize = 0;
    char *returnedstring = malloc(sizeof(char));
    while ((found_position = self->find(self, to_replace)) != -1) {

        returnedstring = realloc(returnedstring, sizeof(char) * (returnedsize + found_position + replacement_length));

        for (int i = 0; i < found_position; i++) {
            returnedstring[returnedsize + i] = self->value[i];
        }

        for (int i = 0; i < replacement_length; i++) {
            returnedstring[returnedsize + found_position + i] = replacement[i];
        }

        returnedsize += found_position + replacement_length;
        self->value += found_position + to_replace_len;
    }

    if (self->value[0] != '\0') {

        int endlength = self->length(self);
        returnedstring = realloc(returnedstring, returnedsize + endlength + 1);
        
        for (int i = 0; self->value[i] != '\0'; i++) {
            returnedstring[returnedsize + i] = self->value[i];
        }

        returnedsize += endlength;
    }
    returnedstring[returnedsize] = '\0';

    free(self->value);
    self->value = returnedstring;
    self->size = returnedsize;
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
        stringlen + 1,
        &string_print,
        &string_input,
        &string_resize,
        &string_length,
        &string_append,
        &string_find,
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

#define FILESTREAM_APPEND 16
#define FILESTREAM_TRUNC 8
#define FILESTREAM_READ 4
#define FILESTREAM_WRITE 2
#define FILESTREAM_BINARY 1

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

filestream initFilestream(char *filename, int options) {

    filestream file_default = {
        &filestream_read,
        &filestream_write
    };

    switch (options) {
        case 2:
            file_default.desc = fopen(filename, "w");
            break;
        case 3:
            file_default.desc = fopen(filename, "wb");
            break;
        case 4:
            file_default.desc = fopen(filename, "r");
            break;
        case 5:
            file_default.desc = fopen(filename, "rb");
            break;
        case 6:
            file_default.desc = fopen(filename, "r+");
            break;
        case 7:
            file_default.desc = fopen(filename, "r+b");
            break;
        case 8:
            file_default.desc = fopen(filename, "w+");
            break;
        case 9:
            file_default.desc = fopen(filename, "w+b");
            break;
        case 16:
            file_default.desc = fopen(filename, "a");
            break;
        case 17:
            file_default.desc = fopen(filename, "ab");
            break;
        case 20:
            file_default.desc = fopen(filename, "a+");
            break;
        case 21:
            file_default.desc = fopen(filename, "a+b");
            break;
        default:
            printf("ERROR: Incorrect use of file options.");
            exit(1);
    }

    fseek(file_default.desc, 0, SEEK_END);
    file_default.size = ftell(file_default.desc);
    rewind(file_default.desc);
    
    return file_default;
}
