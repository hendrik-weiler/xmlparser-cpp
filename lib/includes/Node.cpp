//
// Created by Hendrik Weiler on 28.12.24.
//

#include "Node.h"

#include <iostream>
#include <ostream>

std::string xmlparser::Node::toXML() {
    std::string xml = "<" + name;
    for (auto const& x : attributes) {
        xml += " " + x.first + "=\"" + x.second + "\"";
    }
    if (content.empty() && children.empty()) {
        xml += "/>";
    } else {
        xml += ">";
        if (!content.empty()) {
            if (isCDATA) {
                xml += "<![CDATA[" + content + "]]>";
            } else {
                xml += content;
            }
        }
        for (Node* child : children) {
            xml += child->toXML();
        }
        xml += "</" + name + ">";
    }
    return xml;
}

void xmlparser::Node::toString() {
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

void xmlparser::Node::destroy() {
    for (Node* child : children) {
        child->destroy();
    }
}
