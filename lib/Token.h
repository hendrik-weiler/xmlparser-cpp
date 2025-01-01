//
// Created by Hendrik Weiler on 28.12.24.
//

#ifndef TOKEN_H
#define TOKEN_H
#include <string>

#include "Type.h"

namespace xmlparser {
    class Token {
    public:
        Type type;
        std::string value;
        Token(Type type, std::string value) : type(type), value(value) {}
        void toString();
    };
}
#endif //TOKEN_H
