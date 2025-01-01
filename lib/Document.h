//
// Created by Hendrik Weiler on 28.12.24.
//

#ifndef DOCUMENT_H
#define DOCUMENT_H
#include "includes/Node.h"


namespace xmlparser {
    class Document {
    public:
        std::unordered_map<std::string, std::vector<xmlparser::Node*>> tagNodes;
        std::unordered_map<std::string, std::unordered_map<std::string,std::string>> declarations;
        void addTagNode(std::string tag, xmlparser::Node* node);
        void addDeclarationAttribute(std::string declaration, std::string attribute, std::string value);
        std::string getDeclarationAttribute(std::string declaration, std::string attribute);
        std::string toXML();

        xmlparser::Node *root;
    };
}

#endif //DOCUMENT_H
