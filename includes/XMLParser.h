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
};

#endif //MYCLASS_H
