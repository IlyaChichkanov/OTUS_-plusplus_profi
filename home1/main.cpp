#include "lib.h"

#include <iostream>

int main (int, char **) {
    std::cout << "build: " << build_version() << std::endl;
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
