#include "XMLParser.h"

#include "../Parser.h"

void xmlparser::XMLParser::parse(std::string text) {
    //Lexer lexer(text);
    //lexer.sum();
    parser = new Parser(text);
    parser->parse();
    //parser->document->root->toString();
}

void xmlparser::XMLParser::destroy() {
    delete parser;
}

std::string xmlparser::XMLParser::toXML() {
    return parser->document->toXML();
}

std::vector<xmlparser::Node *> xmlparser::XMLParser::getElementsByName(std::string tag) {
    if (parser->document->tagNodes.contains(tag)) {
        return parser->document->tagNodes[tag];
    }
    return std::vector<xmlparser::Node *>(0);
}

std::string xmlparser::XMLParser::getDeclarationAttribute(std::string declaration, std::string attribute) {
    return parser->document->getDeclarationAttribute(declaration, attribute);
}
