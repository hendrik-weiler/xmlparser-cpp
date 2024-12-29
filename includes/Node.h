//
// Created by Hendrik Weiler on 28.12.24.
//

#ifndef NODE_H
#define NODE_H
#include <unordered_map>
#include <vector>


class Node {
public:
    Node* parent;
    std::vector<Node*> children;
    std::string id;
    std::string name;
    std::string content;
    std::unordered_map<std::string,std::string> attributes;
    virtual void toString();
    virtual void destroy();
};



#endif //NODE_H
