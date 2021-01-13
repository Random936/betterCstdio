#include "bettercstdio.h"

int main() {

    string teststring = initString("This is my test string");
    teststring.replace(&teststring, "test", "stringy");
    teststring.print(&teststring);

    return 0;
}