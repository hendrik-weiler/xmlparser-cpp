//
// Created by Hendrik Weiler on 28.12.24.
//

#ifndef NODE_H
#define NODE_H
#include <unordered_map>
#include <vector>

class Node {
public:
    bool isCDATA = false;
    bool isRoot = false;
    Node* parent;
    std::vector<Node*> children;
    std::string id;
    std::string name;
    std::string content;
    std::unordered_map<std::string,std::string> attributes;

    virtual std::string toXML();

    virtual void toString();
    virtual void destroy();
};


#endif //NODE_H
