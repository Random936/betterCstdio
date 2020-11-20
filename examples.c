#include "immutablestrings.h"

int main() {

    // Better String features!
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

    // Simple Linked List features!
    list linkedlist = initList();
    linkedlist.createNode(&linkedlist, "String!");
    linkedlist.print(&linkedlist);

    return 0;
}