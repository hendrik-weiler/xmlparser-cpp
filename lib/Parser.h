//
// Created by Hendrik Weiler on 28.12.24.
//

#ifndef PARSER_H
#define PARSER_H
#include "Document.h"
#include "Lexer.h"


class Parser {
private:
    Lexer* lexer;
    Token currentToken{Type::END_OF_FILE, "EOF"};
    Node* currentNode;
public:
    Document* document;
    Parser(std::string text);
    ~Parser();
    bool inList(std::vector<Type> list, Token token);

    void node(std::vector<Node *> *children, Node *parent);

    void parse();
    void eat(Type type);
};



#endif //PARSER_H
