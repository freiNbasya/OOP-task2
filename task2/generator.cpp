#include "generator.h"

int Generator::generateID() {
    static bool seedInitialized = false;
    if (!seedInitialized) {
        std::srand(static_cast<unsigned>(std::time(0)));
        seedInitialized = true;
    }
    return std::rand();
}