//
// Created by Hendrik Weiler on 28.12.24.
//

#include "Lexer.h"

#include <iostream>

void Lexer::addPos() {
    pos += 1;
    linePos += 1;
    this->currentChar = text[pos];
}

bool Lexer::isIdentifier(char c) {
    return isalnum(c)
        || c == '.'
        || c == '@';
}

std::string Lexer::findIdentifier() {
    std::string identifier = "";
    while (this->currentChar != ' '
        && this->currentChar != '\n'
        && this->currentChar != '\t'
        && this->currentChar != '>'
        && isalnum(this->currentChar)
        || this->currentChar == '.'
        || this->currentChar == '-'
        || this->currentChar == '@') {

        if (pos >= text.size()) {
            break;
        }

        identifier += this->currentChar;
        addPos();
    }
    return identifier;
}

std::string Lexer::findValue() {
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

std::string Lexer::findInnerText() {
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

Token Lexer::getNextToken() {

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

    if (!inTag) {
        return Token(Type::INNER_TEXT, findInnerText());
    } else {
        if (isIdentifier(this->currentChar)) {
            return Token(Type::IDENTIFIER, findIdentifier());
        }
    }

    error();

    return Token(Type::END_OF_FILE, "EOF");
}

void Lexer::error() {
    std::cout << "Unexpected character: " << this->currentChar << ", pos: " << linePos << ", line: " << line << std::endl;
}

char Lexer::peek(int num) {
    int thePos = pos + num;
    if (thePos > text.size()) {
        return '\0';
    }
    return text[thePos];
}

void Lexer::sum() {

    Token token = getNextToken();
    token.toString();
    while (token.type != Type::END_OF_FILE) {
        token = getNextToken();
        token.toString();
    }

}
