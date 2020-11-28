#include "immutablestrings.h"

// This function is used to create a node template.
declareLinkedList(int, listnode)

int main() {

    // Simple Linked List features!
    printf("-----BETTER LINKED LIST FEATURES-----\n");
    
    list newlist;
    list_createNode(&newlist, 32);
    list_createNode(&newlist, 52);
    list_createNode(&newlist, 62);
    list_print(&newlist, "%d\n");
    printf("Length: %d\n", newlist.valuesize);

    // Better String features!
    printf("\n-----BETTER STRING FEATURES-----\n");

    string test = initString("Tester");
    test.print(&test);
    test.append(&test, " test!");
    test.print(&test);
    printf("Found: %d, Length: %d\n", test.find(&test, "test"), test.length(&test));
    printf("Substring: %s\n", test.substr(&test, 7, 11));
    test.replace(&test, "test", "supercalafragalisticexpialadocious");
    printf("Replaced: %s\n", test.value);
    printf("Userinput test: ");
    test.input(&test, 1024);
    printf("User typed: %s\nThe length was %d\n", test.value, test.length(&test));

    return 0;
}
