//
// Created by Hendrik Weiler on 29.12.24.
//

#ifndef XMLPARSERLOADER_H
#define XMLPARSERLOADER_H
#include <iostream>
#include <string>
#include <dlfcn.h>

class XMLParser;

class XMLParserLoader {
private:
    void* handle;
public:
    explicit XMLParserLoader(const std::string& libpath) {
        handle = dlopen(libpath.c_str(), RTLD_NOW);
        if (!handle) {
            std::cerr << "Cannot open library: " << dlerror() << '\n';
        }
        dlerror();
    }
    XMLParser* create() {
        typedef XMLParser* (*create_t)();
        create_t create = (create_t) dlsym(handle, "create");
        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            std::cerr << "Cannot load symbol 'function_name': " << dlsym_error << '\n';
            dlclose(handle);
            return nullptr;
        }
        return create();
    }
    void destroy(XMLParser* instance) {
        typedef void (*destroy_t)(XMLParser*);
        destroy_t destroy = (destroy_t) dlsym(handle, "destroy");
        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            std::cerr << "Cannot load symbol 'destroy': " << dlsym_error << '\n';
            dlclose(handle);
            return;
        }
        destroy(instance);
        dlclose(handle);
    }
};

#endif //XMLPARSERLOADER_H
