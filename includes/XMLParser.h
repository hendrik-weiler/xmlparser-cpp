#ifndef MYCLASS_H
#define MYCLASS_H

#include <iostream>
#include "Node.h"

class XMLParser {
public:
    virtual ~XMLParser() = default;
    virtual void parse(std::string text);
    virtual void destroy();
    virtual std::vector<Node*> getElementsByName(std::string tag);
    virtual std::string getDeclarationAttribute(std::string declaration, std::string attribute);
};

#endif //MYCLASS_H
