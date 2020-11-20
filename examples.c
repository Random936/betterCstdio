#include "immutablestrings.h"

int main() {

    

    // Simple Linked List features!
    printf("-----BETTER LINKED LIST FEATURES-----\n");
    
    list linkedlist = initList();
    linkedlist.createNode(&linkedlist, "This");
    linkedlist.createNode(&linkedlist, "prints");
    linkedlist.createNode(&linkedlist, "backwards!");
    linkedlist.print(&linkedlist);

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
    test.input(&test, 5);
    printf("User typed: ");
    test.print(&test);

    return 0;
}