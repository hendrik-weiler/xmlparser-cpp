//
// Created by Hendrik Weiler on 28.12.24.
//

#ifndef LEXER_H
#define LEXER_H
#include <string>

#include "Token.h"

namespace xmlparser {
    class Lexer {
    private:
        std::string text;
        int pos;
        int line;
        int linePos;
        char currentChar;
        bool inTag = false;
        bool inDeclaration = false;
        bool inComment = false;
        bool inCDATA = false;
    protected:
        void addPos();

        bool isIdentifier(char c);

        std::string findIdentifier();

        std::string findValue();

        std::string findInnerText();

        std::string findTextByEnd(std::string endSequence);

    public:
        Lexer(std::string text) : text(text), pos(0), line(1), linePos(0) {}
        Token getNextToken();

        void error();
        char peek(int num = 1);

        bool findKeyword(std::string keyword, int num = 1) const;

        void advance(int i);

        void sum();
    };
}

#endif //LEXER_H
