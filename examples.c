#include "bettercstdio.h"

// This function is used to create a node template.
declareLinkedList(int, intnode)
declareLinkedList(char *, charnode)

int main() {

    printf("-----BETTER LINKED LIST FEATURES-----\n");
    
    list charlist = initList_charnode();
    charlist.create(&charlist, "This is the first string!");
    charlist.create(&charlist, "This is the second string!");
    charlist.create(&charlist, "This is the last string!");
    printf("\nBefore Deletion:\n");
    charlist.remove(&charlist, 2, "This was inserted!");
    charlist.print(&charlist, "\t%s\n");
    printf("\tLength: %d\n\n", charlist.valuesize);
    charlist.remove(&charlist, 2);
    printf("After Deletion of %d:\n", 2);
    charlist.print(&charlist, "\t%s\n");
    printf("\tLength: %d\n", charlist.valuesize);
    
    list intlist = initList_intnode();
    intlist.create(&intlist, 11);
    intlist.create(&intlist, 22);
    intlist.create(&intlist, 33);
    printf("\nBefore Deletion:\n");
    intlist.insert(&intlist, 3, 1337);
    intlist.print(&intlist, "\t%d\n");
    printf("\tLength: %d\n\n", intlist.valuesize);
    intlist.remove(&intlist, 1);
    printf("After Deletion of %d:\n", 1);
    intlist.print(&intlist, "\t%d\n");
    printf("\tLength: %d\n", intlist.valuesize);


    printf("\n-----BETTER STRING FEATURES-----\n");

    string test = initString("Tester");
    test.print(&test);
    test.append(&test, " test! Also this.");
    test.append(&test, " Did I mention this is a test? Yes!");
    test.print(&test);
    printf("Found: %d, Length: %d\n", test.find(&test, "test", 0), test.length(&test));
    printf("Substring: %s\n", test.substr(&test, 7, 11));
    test.replace(&test, "test", "pneumonoultramicroscopicsilicovolcanoconiosis");
    printf("Replaced: %s\n", test.value);
    printf("Userinput test: ");
    test.input(&test, 10);
    printf("User typed: %s\nThe length was: %d\n", test.value, test.length(&test));


    printf("\n-----BETTER FILES-----\n");

    filestream writetest = initFilestream("filetest.txt", "w");
    writetest.write(&writetest, "This will be written to the file.", sizeof(char) * 33);
    printf("File size: %d\n", writetest.size);
    fclose(writetest.desc);

    filestream readtest = initFilestream("filetest.txt", "r");
    printf("File content: %s\n", readtest.read(&readtest));
    fclose(readtest.desc);

    return 0;
}
