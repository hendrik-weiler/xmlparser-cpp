#include "library.h"

#include "XMLParser.h"

extern "C" XMLParser* create() {
    return new XMLParser();
}

extern "C" void destroy(XMLParser* instance) {
    delete instance;
}

