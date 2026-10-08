#include <superAwesome/superAwesome.h>
#include <superAwesome/version.h>
#include <cstdio>
#include <iostream>


int main() {
    std::printf("Super Awesome Version: %s\n", SUPER_AWESOME_VERSION_STRING);

#if SUPER_AWESOME_VERSION == 100 // version 0.1.0
    auto value = rd::SuperAwesomeFunction();
#elif SUPER_AWESOME_VERSION == 200 // version 0.2.0
    auto value = rd::SuperAwesomeFunction(1);
#endif

    std::printf("Super Awesome Function returned: %d", value);
    return 0;
}