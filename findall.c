#include "bettercstdio.h"

int main() {

    string teststr = initString("Hello, this will be removed because this, the word this, will be replaced with this...");
    teststr.print(&teststr);
    int *positions = teststr.findall(&teststr, "this");

    for (int i = 0; positions[i] != 0; i++) {
        printf("%d %s\n", positions[i], teststr.substr(&teststr, positions[i] - 4, positions[i] + 8));
    }

    return 0;
}