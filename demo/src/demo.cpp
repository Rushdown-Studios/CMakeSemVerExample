#include <superAwesome/superAwesome.h>
#include <superAwesome/version.h>
#include <cstdio>
#include <iostream>


int main() {
    std::printf("Super Awesome Version: %s\n", SUPER_AWESOME_VERSION_STRING);

#if SUPER_AWESOME_VERSION == 100 // version 0.1.0
    auto value = rd::SuperAwesomeFunction();
#endif

    std::printf("Super Awesome Function returned: %d", value);
    return 0;
}