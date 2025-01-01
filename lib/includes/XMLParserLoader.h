//
// Created by Hendrik Weiler on 29.12.24.
//

#ifndef XMLPARSERLOADER_H
#define XMLPARSERLOADER_H
#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace xmlparser {
    class XMLParserLoader {
    private:
#ifdef _WIN32
        HMODULE handle;
#else
        void* handle;
#endif

    public:
        explicit XMLParserLoader(const std::string& libpath) {
#ifdef _WIN32
            handle = LoadLibrary(TEXT(libpath.c_str()));
            if (handle == nullptr) {
                std::cerr << "Could not load the DLL" << std::endl;
            }
#else
            handle = dlopen(libpath.c_str(), RTLD_NOW);
            if (!handle) {
                std::cerr << "Cannot open library: " << dlerror() << '\n';
            }
            dlerror();
#endif
        }
        XMLParser* create() {
#ifdef _WIN32
            typedef XMLParser* (*create_t)();
            create_t create = (create_t) GetProcAddress(handle, "create");
            if (create == nullptr) {
                std::cerr << "Cannot load symbol 'create': " << '\n';
                FreeLibrary(handle);
                return nullptr;
            }
            return create();
#else
            typedef XMLParser* (*create_t)();
            create_t create = (create_t) dlsym(handle, "create");
            const char* dlsym_error = dlerror();
            if (dlsym_error) {
                std::cerr << "Cannot load symbol 'function_name': " << dlsym_error << '\n';
                dlclose(handle);
                return nullptr;
            }
            return create();
#endif
        }
        void destroy(XMLParser* instance) {
#ifdef _WIN32
            typedef XMLParser* (*destroy_t)(XMLParser*);
            destroy_t destroy = (destroy_t) GetProcAddress(handle, "destroy");
            if (destroy == nullptr) {
                std::cerr << "Cannot load symbol 'destroy': " << '\n';
                FreeLibrary(handle);
                return;
            }
            destroy(instance);
            FreeLibrary(handle);
#else
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
#endif

        }
    };
}

#endif //XMLPARSERLOADER_H
