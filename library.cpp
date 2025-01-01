#include "library.h"

#include "lib/includes/XMLParser.h"

extern "C" EXPORT XMLParser* create() {
    return new XMLParser();
}

extern "C" EXPORT void destroy(XMLParser* instance) {
    delete instance;
}