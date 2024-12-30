#include "library.h"

#include "XMLParser.h"

extern "C" EXPORT XMLParser* create() {
    return new XMLParser();
}

extern "C" EXPORT void destroy(XMLParser* instance) {
    delete instance;
}

