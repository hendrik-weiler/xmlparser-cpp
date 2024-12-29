//
// Created by Hendrik Weiler on 28.12.24.
//

#ifndef DOCUMENT_H
#define DOCUMENT_H
#include "Node.h"


class Document {
public:
    std::unordered_map<std::string, std::vector<Node*>> tagNodes;
    void addTagNode(std::string tag, Node* node);
    Node *root;
};



#endif //DOCUMENT_H
