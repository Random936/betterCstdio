#include "simplewebrequests.h"

int main() {

    http_t test;
    http_get(&test, "www.google.com");

    return 0;
}