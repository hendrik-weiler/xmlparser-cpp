//
// Created by Hendrik Weiler on 28.12.24.
//

#include "Node.h"

#include <iostream>
#include <ostream>

void Node::toString() {
    std::cout << "Node: "
    << name
    << ", Children: "
    << children.size()
    << ", Content: "
    << content
    << std::endl;
    std::cout << "Attributes: ";
    for (auto const& x : attributes) {
        std::cout << x.first
        << ": "
        << x.second
        << ", ";
    }
    std::cout << std::endl;
    for (Node* child : children) {
        std::cout << "- ";
        child->toString();
    }
}

void Node::destroy() {
    for (Node* child : children) {
        child->destroy();
    }
}
