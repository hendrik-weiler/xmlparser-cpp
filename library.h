#ifndef XMLPARSER_LIBRARY_H
#define XMLPARSER_LIBRARY_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif

#endif //XMLPARSER_LIBRARY_H