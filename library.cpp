#include "library.h"

#include "lib/includes/XMLParser.h"

extern "C" EXPORT xmlparser::XMLParser* create() {
    return new xmlparser::XMLParser();
}

extern "C" EXPORT void destroy(xmlparser::XMLParser* instance) {
    delete instance;
}