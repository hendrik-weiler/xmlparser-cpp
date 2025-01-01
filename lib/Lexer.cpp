//
// Created by Hendrik Weiler on 28.12.24.
//

#include "Lexer.h"

#include <iostream>

void xmlparser::Lexer::addPos() {
    pos += 1;
    linePos += 1;
    this->currentChar = text[pos];
}

bool xmlparser::Lexer::isIdentifier(char c) {
    return isalnum(c)
        || c == '.'
        || c == '@';
}

std::string xmlparser::Lexer::findIdentifier() {
    std::string identifier = "";
    while (this->currentChar != ' '
        && this->currentChar != '\n'
        && this->currentChar != '\t'
        && this->currentChar != '>'
        && isalnum(this->currentChar)
        || this->currentChar == '.'
        || this->currentChar == '-'
        || this->currentChar == '@'
        || this->currentChar == ':') {

        if (pos >= text.size()) {
            break;
        }

        identifier += this->currentChar;
        addPos();
    }
    return identifier;
}

std::string xmlparser::Lexer::findValue() {
    std::string value = "";
    while (this->currentChar != '"'
        && this->currentChar != '\'') {

        if (pos >= text.size()) {
            break;
        }

        value += this->currentChar;
        addPos();
    }
    addPos();
    return value;
}

std::string xmlparser::Lexer::findInnerText() {
    std::string value = "";
    while (this->currentChar != '<') {

        if (pos >= text.size()) {
            break;
        }

        value += this->currentChar;
        addPos();
        }
    return value;
}

std::string xmlparser::Lexer::findTextByEnd(std::string endSequence) {
    std::string value = "";
    while (!findKeyword(endSequence, endSequence.size())) {

        if (pos >= text.size()) {
            break;
        }

        value += this->currentChar;
        addPos();
    }
    return value;
}

xmlparser::Token xmlparser::Lexer::getNextToken() {

    if (pos >= text.size()) {
        return Token(Type::END_OF_FILE, "EOF");
    }

    this->currentChar = text[pos];

    if (this->currentChar == '\n') {
        line += 1;
        linePos = 0;
        addPos();
        return getNextToken();
    }
    if (this->currentChar == ' ' || this->currentChar == '\t') {
        addPos();
        return getNextToken();
    }

    if (findKeyword("]]>", 3)) {
        advance(3);
        inCDATA = false;
        return Token(Type::CDATA_END, "]]>");
    }

    if (inCDATA) {
        return Token(Type::INNER_TEXT, findTextByEnd("]]>"));
    }

    if (findKeyword("<![CDATA[", 9)) {
        advance(9);
        inCDATA = true;
        return Token(Type::CDATA_START, "<![CDATA[");
    }

    if (findKeyword("-->", 3)) {
        advance(3);
        inComment = false;
        return Token(Type::COMMENT_END, "-->");
    }

    if (findKeyword("<!--", 4)) {
        advance(4);
        inComment = true;
        return Token(Type::COMMENT_START, "<!--");
    }

    if (this->currentChar == '?' && peek() == '>') {
        addPos();
        addPos();
        inDeclaration = false;
        return Token(Type::DECLARATION_END, "?>");
    }

    if (this->currentChar == '<' && peek() == '?') {
        addPos();
        addPos();
        inDeclaration = true;
        return Token(Type::DECLARATION_START, "<?");
    }

    if (this->currentChar == '<') {
        if (peek() == '/') {
            addPos();
            addPos();
            inTag = true;
            return Token(Type::SLASH_OPEN_TAG, "</");
        } else {
            addPos();
            inTag = true;
            return Token(Type::OPEN_TAG, "<");
        }
    }

    if (this->currentChar == '>') {
        addPos();
        inTag = false;
        return Token(Type::CLOSE_TAG, ">");
    }

    if (this->currentChar == '/') {
        if (peek() == '>') {
            addPos();
            addPos();
            return Token(Type::SLASH_CLOSE_TAG, "/>");
        } else {
            addPos();
            return Token(Type::SLASH, "/");
        }
    }

    if (this->currentChar == '=') {
        addPos();
        return Token(Type::EQUAL, "=");
    }

    if (this->currentChar == '"'
        || this->currentChar == '\'') {
        addPos();
        return Token(Type::ATTRIBUTE_VALUE, findValue());
    }

    if (inComment) {
        return Token(Type::INNER_TEXT, findTextByEnd("-->"));
    } else {
        if (!inTag && !inDeclaration) {
            return Token(Type::INNER_TEXT, findInnerText());
        } else {
            if (isIdentifier(this->currentChar)) {
                return Token(Type::IDENTIFIER, findIdentifier());
            }
        }
    }

    error();

    return Token(Type::END_OF_FILE, "EOF");
}

void xmlparser::Lexer::error() {
    std::cout << "Unexpected character: " << this->currentChar << ", pos: " << linePos << ", line: " << line << std::endl;
}

char xmlparser::Lexer::peek(int num) {
    int thePos = pos + num;
    if (thePos > text.size()) {
        return '\0';
    }
    return text[thePos];
}

bool xmlparser::Lexer::findKeyword(std::string keyword, int num) const {
    std::string value = "";
    for(int i = 0; i < num; i++) {
        value += text[pos + i];
    }
    return value == keyword;
}

void xmlparser::Lexer::advance(int i) {
    for (int j = 0; j < i; ++j) addPos();
}

void xmlparser::Lexer::sum() {

    Token token = getNextToken();
    token.toString();
    while (token.type != Type::END_OF_FILE) {
        token = getNextToken();
        token.toString();
    }

}
