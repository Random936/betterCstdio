#include "immutablestrings.h"

// This function is used to create a node template.
declareLinkedList(int, intnode)
declareLinkedList(char *, charnode)

int main() {

    printf("-----BETTER LINKED LIST FEATURES-----\n");
    
    list charlist = initList_charnode();
    charlist.createNode(&charlist, "This is a string!");
    charlist.createNode(&charlist, "This is the second string!");
    charlist.createNode(&charlist, "This is the last string!");
    charlist.print(&charlist, "%s\n");
    printf("Length: %d\n", charlist.valuesize);
    
    list intlist = initList_intnode();
    intlist.createNode(&intlist, 24);
    intlist.createNode(&intlist, 25);
    intlist.createNode(&intlist, 26);
    intlist.print(&intlist, "%d\n");
    printf("Length: %d\n", intlist.valuesize);


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
