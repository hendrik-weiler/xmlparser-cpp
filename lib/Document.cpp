//
// Created by Hendrik Weiler on 28.12.24.
//

#include "Document.h"

void Document::addTagNode(std::string tag, Node *node) {
    if (tagNodes.find(tag) == tagNodes.end()) {
        tagNodes[tag] = std::vector<Node*>();
    }
    tagNodes[tag].push_back(node);
}
