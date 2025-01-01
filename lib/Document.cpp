//
// Created by Hendrik Weiler on 28.12.24.
//

#include "Document.h"

void xmlparser::Document::addTagNode(std::string tag, xmlparser::Node *node) {
    if (tagNodes.find(tag) == tagNodes.end()) {
        tagNodes[tag] = std::vector<xmlparser::Node*>();
    }
    tagNodes[tag].push_back(node);
}

void xmlparser::Document::addDeclarationAttribute(std::string declaration, std::string attribute, std::string value) {
    if (declarations.find(declaration) == declarations.end()) {
        declarations[declaration] = std::unordered_map<std::string, std::string>();
    }
    declarations[declaration][attribute] = value;
}

std::string xmlparser::Document::getDeclarationAttribute(std::string declaration, std::string attribute) {
    if (declarations.find(declaration) != declarations.end()) {
        if (declarations[declaration].find(attribute) != declarations[declaration].end()) {
            return declarations[declaration][attribute];
        }
    }
    return "";
}

std::string xmlparser::Document::toXML() {
    if (this->root != nullptr) {
        std::string version = getDeclarationAttribute("xml", "version");
        std::string encoding = getDeclarationAttribute("xml", "encoding");
        if (!version.empty() && !encoding.empty()) {
            return "<?xml version=\"" + version + "\" encoding=\"" + encoding + "\"?>" + this->root->toXML();
        }
        return this->root->toXML();
    }
    return "";
}
