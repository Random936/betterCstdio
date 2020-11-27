#include "immutablestrings.h"
#include "simplelinkedlists.h"

// This function is used to create a node template.
declareLinkedList(char *, list_s, list, listnode_s, listnode)

int main() {

    // Simple Linked List features!
    printf("-----BETTER LINKED LIST FEATURES-----\n");
    
    list linkedlist = initList();
    linkedlist.createNode(&linkedlist, "This");
    linkedlist.createNode(&linkedlist, "prints");
    linkedlist.createNode(&linkedlist, "backwards!");
    linkedlist.print(&linkedlist, "%s\n");

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
