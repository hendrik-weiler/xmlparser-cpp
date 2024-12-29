//
// Created by Hendrik Weiler on 28.12.24.
//

#include "Parser.h"

#include <iostream>
#include <ostream>

Parser::Parser(std::string text) {
    this->lexer = new Lexer(text);
    this->document = new Document();
    this->currentToken = lexer->getNextToken();
    this->currentNode = nullptr;
}

Parser::~Parser() {
    delete this->lexer;

    for (Node* node : this->document->root->children) {
        node->destroy();
    }

    delete this->document;
}

bool Parser::inList(std::vector<Type> list, Token token) {
    return std::find(list.begin(), list.end(), token.type) != list.end();
}

void Parser::node(std::vector<Node*> *children, Node* parent) {
    Node* node = nullptr;

    while (inList({Type::OPEN_TAG, Type::COMMENT_START}, this->currentToken)) {
        if (this->currentToken.type == Type::OPEN_TAG) {
            eat(Type::OPEN_TAG);
            if (this->currentToken.type == Type::IDENTIFIER) {
                node = new Node();
                node->parent = parent;
                if (parent == nullptr) {
                    this->document->root = node;
                } else {
                    children->push_back(node);
                }
                node->name = currentToken.value;
                document->addTagNode(node->name, node);
                //std::cout << "!Node: " << node->name << std::endl;
                eat(Type::IDENTIFIER);
            }

            while (inList({Type::IDENTIFIER, Type::ATTRIBUTE_VALUE}, this->currentToken)) {
                std::string name = currentToken.value;
                eat(Type::IDENTIFIER);
                eat(Type::EQUAL);
                node->attributes[name] = currentToken.value;
                eat(Type::ATTRIBUTE_VALUE);
            }
            if (currentToken.type == Type::SLASH_CLOSE_TAG) {
                eat(Type::SLASH_CLOSE_TAG);
                this->node(&parent->children, parent);
                return;
            }
            eat(Type::CLOSE_TAG);

            if (this->currentToken.type == Type::CDATA_START) {
                eat(Type::CDATA_START);
                node->content = currentToken.value;
                eat(Type::INNER_TEXT);
                eat(Type::CDATA_END);
            } else {

                if (this->currentToken.type == Type::INNER_TEXT) {
                    node->content = currentToken.value;
                    eat(Type::INNER_TEXT);
                }

                this->node(&node->children, node);

                if (this->currentToken.type == Type::INNER_TEXT) {
                    node->content += currentToken.value;
                    eat(Type::INNER_TEXT);
                }

            }

            if (this->currentToken.type == Type::SLASH_OPEN_TAG) {
                eat(Type::SLASH_OPEN_TAG);
                eat(Type::IDENTIFIER);
                eat(Type::CLOSE_TAG);
            }
        }
        if (this->currentToken.type == Type::COMMENT_START) {
            eat(Type::COMMENT_START);
            while (this->currentToken.type != Type::COMMENT_END) {
                eat(this->currentToken.type);
            }
            eat(Type::COMMENT_END);
        }
    }
}

void Parser::parse() {

    while (inList({Type::OPEN_TAG, Type::DECLARATION_START}, this->currentToken)) {
        if (this->currentToken.type == Type::OPEN_TAG) {
            this->node(nullptr,nullptr);
        }
        if (this->currentToken.type == Type::DECLARATION_START) {
            eat(Type::DECLARATION_START);
            currentDeclaration = currentToken.value;
            eat(Type::IDENTIFIER);
            while (inList({Type::IDENTIFIER}, this->currentToken)) {
                std::string name = currentToken.value;
                eat(Type::IDENTIFIER);
                eat(Type::EQUAL);
                std::string value = currentToken.value;
                eat(Type::ATTRIBUTE_VALUE);
                document->addDeclarationAttribute(currentDeclaration, name, value);
            }
            eat(Type::DECLARATION_END);
        }
    }

}

void Parser::eat(Type type) {
    //std::cout << "trying to eat " << type << " current: " << this->currentToken.type << ",content:" << this->currentToken.value << std::endl;
    if (this->currentToken.type == type) {
        this->currentToken = lexer->getNextToken();
    } else {
        this->lexer->error();
    }
}
