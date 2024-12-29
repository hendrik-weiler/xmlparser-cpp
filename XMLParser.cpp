#include "XMLParser.h"

#include "lib/Parser.h"

void XMLParser::parse(std::string text) {
    //Lexer lexer(text);
    //lexer.sum();
    parser = new Parser(text);
    parser->parse();
    //parser->document->root->toString();
}

void XMLParser::destroy() {
    delete parser;
}

std::vector<Node *> XMLParser::getElementsByName(std::string tag) {
    if (parser->document->tagNodes.contains(tag)) {
        return parser->document->tagNodes[tag];
    }
    return std::vector<Node *>(0);
}
